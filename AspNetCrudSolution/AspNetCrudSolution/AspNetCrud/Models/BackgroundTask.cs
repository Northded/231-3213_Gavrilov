namespace AspNetCrud.Models;

public class BackgroundTask
{
    public string Id { get; set; } = Guid.NewGuid().ToString();
    public string Status { get; set; } = "Queued";
    public string? Result { get; set; }
    public DateTime StartTime { get; set; } = DateTime.UtcNow;
    public DateTime? EndTime { get; set; }
    public string? ContainerId { get; set; }
}