using AspNetCrud.Data; // Добавляем эту директиву
using AspNetCrud.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace AspNetCrud.Services;

public class TaskService : ITaskService
{
    private readonly IServiceProvider _serviceProvider;
    private readonly ILogger<TaskService> _logger;
    private readonly ConcurrentQueue<string> _taskQueue = new();
    private readonly SemaphoreSlim _semaphore = new(1, 1);
    private const int MAX_CONCURRENT_TASKS = 10;

    public TaskService(
        IServiceProvider serviceProvider,
        ILogger<TaskService> logger)
    {
        _serviceProvider = serviceProvider;
        _logger = logger;
        
        _logger.LogInformation("TaskService initialized. Starting background queue processor.");
        Task.Run(ProcessTaskQueue);
    }

    public async Task<BackgroundTask> StartTask()
    {
        using var scope = _serviceProvider.CreateScope();
        var context = scope.ServiceProvider.GetRequiredService<ApplicationDbContext>();
        
        var task = new BackgroundTask();
        context.BackgroundTasks.Add(task);
        await context.SaveChangesAsync();

        _taskQueue.Enqueue(task.Id);
        _logger.LogInformation($"Task {task.Id} added to queue. Queue size: {_taskQueue.Count}");
        return task;
    }

    public async Task<BackgroundTask?> GetTask(string id)
    {
        using var scope = _serviceProvider.CreateScope();
        var context = scope.ServiceProvider.GetRequiredService<ApplicationDbContext>();
        return await context.BackgroundTasks.FindAsync(id);
    }

    public async Task UpdateTask(string taskId, string status, string? result)
    {
        using var scope = _serviceProvider.CreateScope();
        var context = scope.ServiceProvider.GetRequiredService<ApplicationDbContext>();
        
        var task = await context.BackgroundTasks.FindAsync(taskId);
        if (task != null)
        {
            task.Status = status;
            task.Result = result;
            task.EndTime = status == "Processing" ? null : DateTime.UtcNow;
            await context.SaveChangesAsync();
            _logger.LogInformation($"Task {taskId} updated to {status}");
        }
        else
        {
            _logger.LogWarning($"Attempted to update non-existent task: {taskId}");
        }
    }

    private async Task ProcessTaskQueue()
    {
        _logger.LogInformation("Background task queue processor started.");
        
        while (true)
        {
            try
            {
                _logger.LogDebug($"Checking queue. Current size: {_taskQueue.Count}");
                
                if (_taskQueue.TryDequeue(out var taskId))
                {
                    _logger.LogInformation($"Dequeued task: {taskId}. Attempting to process...");
                    
                    await _semaphore.WaitAsync();
                    try
                    {
                        using var scope = _serviceProvider.CreateScope();
                        var context = scope.ServiceProvider.GetRequiredService<ApplicationDbContext>();
                        
                        // Check current processing count
                        var processingCount = await context.BackgroundTasks
                            .CountAsync(t => t.Status == "Processing");
                        
                        _logger.LogInformation($"Current processing tasks: {processingCount}/{MAX_CONCURRENT_TASKS}");
                        
                        // Wait if max concurrent tasks reached
                        while (processingCount >= MAX_CONCURRENT_TASKS)
                        {
                            _logger.LogInformation($"Max concurrent tasks reached ({processingCount}/{MAX_CONCURRENT_TASKS}). Waiting...");
                            await Task.Delay(5000);
                            processingCount = await context.BackgroundTasks
                                .CountAsync(t => t.Status == "Processing");
                        }
                        
                        _logger.LogInformation($"Starting processing for task: {taskId}");
                        await ProcessTask(taskId);
                    }
                    finally
                    {
                        _semaphore.Release();
                    }
                }
                else
                {
                    _logger.LogDebug("Queue is empty. Sleeping for 1 second.");
                    await Task.Delay(1000);
                }
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error in task queue processor");
            }
        }
    }

    private async Task ProcessTask(string taskId)
    {
        try
        {
            _logger.LogInformation($"Processing task: {taskId} - Updating status to Processing");
            await UpdateTask(taskId, "Processing", null);
            
            using var scope = _serviceProvider.CreateScope();
            var dockerService = scope.ServiceProvider.GetRequiredService<DockerService>();
            
            _logger.LogInformation($"Starting worker container for task: {taskId}");
            var containerId = await dockerService.StartWorkerContainerAsync(taskId);
            
            _logger.LogInformation($"Worker container {containerId} started for task: {taskId}");
            await UpdateTask(taskId, "Processing", $"Container: {containerId}");
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, $"Error processing task {taskId}");
            await UpdateTask(taskId, "Failed", ex.Message);
        }
    }
}