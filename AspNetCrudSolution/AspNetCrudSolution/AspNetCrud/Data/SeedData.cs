using AspNetCrud.Models;
using System;
using System.Linq;

namespace AspNetCrud.Data;

public static class SeedData
{
    public static void Initialize(ApplicationDbContext context)
    {
        if (context.Employees.Any())
        {
            return; 
        }

        var random = new Random();
        var positions = new[] { "Менеджер", "Инженер", "Аналитик", "Тестировщик" };
        var departments = new[] { "IT", "Финансы", "Маркетинг", "HR" };

        for (int i = 0; i < 100; i++)
        {
            var hireDate = DateTimeOffset.UtcNow.AddDays(-random.Next(1, 1825));
            
            context.Employees.Add(new Employee
            {
                HireDate = hireDate,
                TerminationDate = random.Next(0, 5) == 0 
                    ? hireDate.AddDays(random.Next(1, 1825)) 
                    : null,
                Position = positions[random.Next(positions.Length)],
                Department = departments[random.Next(departments.Length)],
                EmployeeId = $"EMP-{random.Next(100000, 999999)}",
                IsOnLeave = random.Next(0, 100) < 15
            });
        }

        context.SaveChanges();
        Console.WriteLine($"Seeded {context.Employees.Count()} employees");
    }
}