using System;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

class Program
{
    static async Task Main(string[] args)
    {
        Console.WriteLine("Task Worker started");
        
        if (args.Length == 0)
        {
            Console.WriteLine("Task ID is required");
            return;
        }

        var taskId = args[0];
        Console.WriteLine($"Starting task processing for: {taskId}");

        try
        {
            Console.WriteLine("Simulating long task (20 seconds)...");
            await Task.Delay(20000);
            
            Console.WriteLine("Generating result...");
            var random = new Random();
            var result = new string(Enumerable.Repeat("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 10)
                .Select(s => s[random.Next(s.Length)]).ToArray());
            
            Console.WriteLine($"Task completed. Result: {result}");
            
            Console.WriteLine("Reporting result to main application...");
            using var client = new HttpClient();
            var updateData = new
            {
                status = "Completed",
                result
            };
            
            var content = new StringContent(
                JsonSerializer.Serialize(updateData),
                Encoding.UTF8,
                "application/json"
            );
            
            var url = $"http://host.docker.internal:5171/api/task/{taskId}";
            Console.WriteLine($"Sending PATCH to: {url}");
            
            var response = await client.PatchAsync(url, content);
            Console.WriteLine($"Update response: {response.StatusCode}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error processing task: {ex}");
            
            try
            {
                Console.WriteLine("Reporting failure to main application...");
                using var client = new HttpClient();
                var updateData = new
                {
                    status = "Failed",
                    result = ex.Message
                };
                
                var content = new StringContent(
                    JsonSerializer.Serialize(updateData),
                    Encoding.UTF8,
                    "application/json"
                );
                
                await client.PatchAsync($"http://host.docker.internal:5171/api/task/{taskId}", content);
            }
            catch (Exception innerEx)
            {
                Console.WriteLine($"Failed to report error: {innerEx}");
            }
        }
    }
}