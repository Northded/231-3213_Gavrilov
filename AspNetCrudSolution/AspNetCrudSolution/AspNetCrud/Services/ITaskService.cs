using AspNetCrud.Models;
using System.Threading.Tasks;

namespace AspNetCrud.Services;

public interface ITaskService
{
    Task<BackgroundTask> StartTask();
    Task<BackgroundTask?> GetTask(string id);
    Task UpdateTask(string taskId, string status, string? result);
}