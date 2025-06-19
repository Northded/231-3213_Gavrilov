using Docker.DotNet;
using Docker.DotNet.Models;
using Microsoft.Extensions.Logging;
using System;
using System.Threading.Tasks;

namespace AspNetCrud.Services;

public class DockerService
{
    private readonly DockerClient _client;
    private readonly ILogger<DockerService> _logger;

    public DockerService(ILogger<DockerService> logger)
    {
        _logger = logger;
        try
        {
            _logger.LogInformation("Initializing Docker client...");
            _client = new DockerClientConfiguration(new Uri("unix:///var/run/docker.sock"))
                .CreateClient();
            _logger.LogInformation("Docker client initialized successfully.");
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Failed to create Docker client");
            throw;
        }
    }

    public async Task<string> StartWorkerContainerAsync(string taskId)
    {
        try
        {
            _logger.LogInformation($"Creating container for task: {taskId}");
            
            var createParams = new CreateContainerParameters
            {
                Image = "task-worker",
                Cmd = new[] { taskId },
                HostConfig = new HostConfig
                {
                    AutoRemove = true,
                    NetworkMode = "host"
                }
            };

            var response = await _client.Containers.CreateContainerAsync(createParams);
            _logger.LogInformation($"Container created: {response.ID} for task: {taskId}");
            
            _logger.LogInformation($"Starting container: {response.ID}");
            await _client.Containers.StartContainerAsync(response.ID, new ContainerStartParameters());
            _logger.LogInformation($"Container started: {response.ID}");
            
            return response.ID;
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, $"Error starting worker container for task: {taskId}");
            throw;
        }
    }
}