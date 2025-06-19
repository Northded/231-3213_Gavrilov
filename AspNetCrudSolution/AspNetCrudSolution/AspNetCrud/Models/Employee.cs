namespace AspNetCrud.Models;

public class Employee
{
    public int Id { get; set; }
    public DateTimeOffset HireDate { get; set; } 
    public DateTimeOffset? TerminationDate { get; set; } 
    public required string Position { get; set; }
    public required string Department { get; set; }
    public required string EmployeeId { get; set; }
    public bool IsOnLeave { get; set; }
}