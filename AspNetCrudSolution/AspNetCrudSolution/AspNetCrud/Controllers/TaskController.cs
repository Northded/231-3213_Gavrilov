using AspNetCrud.Services;
using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;

namespace AspNetCrud.Controllers;

[ApiController]
[Route("api/[controller]")]
public class TaskController : ControllerBase
{
    private readonly ITaskService _taskService;
    private readonly ILogger<TaskController> _logger;

    public TaskController(ITaskService taskService, ILogger<TaskController> logger)
    {
        _taskService = taskService;
        _logger = logger;
    }

    [HttpPost]
    public async Task<IActionResult> StartTask()
    {
        try
        {
            var task = await _taskService.StartTask();
            _logger.LogInformation($"Task started: {task.Id}");
            return Accepted(new 
            {
                taskId = task.Id
            });
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error starting task");
            return StatusCode(500, new { error = "Internal server error", details = ex.Message });
        }
    }

    [HttpGet("{id}")]
    public async Task<IActionResult> GetTaskStatus(string id)
    {
        try
        {
            var task = await _taskService.GetTask(id);
            if (task == null)
            {
                _logger.LogWarning($"Task not found: {id}");
                return NotFound(new { error = "Task not found" });
            }

            return Ok(new
            {
                task.Id,
                task.Status,
                task.Result,
                task.StartTime,
                task.EndTime
            });
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, $"Error getting task status: {id}");
            return StatusCode(500, new { error = "Internal server error", details = ex.Message });
        }
    }

    [HttpPatch("{id}")]
    public async Task<IActionResult> UpdateTask(string id, [FromBody] TaskUpdateDto dto)
    {
        try
        {
            await _taskService.UpdateTask(id, dto.Status, dto.Result);
            return NoContent();
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, $"Error updating task: {id}");
            return StatusCode(500, new { error = "Internal server error", details = ex.Message });
        }
    }
}

public record TaskUpdateDto(string Status, string? Result);