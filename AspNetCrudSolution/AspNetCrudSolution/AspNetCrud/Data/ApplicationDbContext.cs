using AspNetCrud.Models;
using Microsoft.EntityFrameworkCore;

namespace AspNetCrud.Data;

public class ApplicationDbContext : DbContext
{
    public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
        : base(options) { }

    public DbSet<Employee> Employees { get; set; }
    public DbSet<BackgroundTask> BackgroundTasks { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);
        
        modelBuilder.Entity<BackgroundTask>(entity =>
        {
            entity.ToTable("BackgroundTasks");
            entity.HasKey(e => e.Id);
            entity.Property(e => e.Status).IsRequired();
            entity.Property(e => e.StartTime).IsRequired();
        });
    }
}