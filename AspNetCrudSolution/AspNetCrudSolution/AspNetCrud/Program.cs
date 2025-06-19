using AspNetCrud.Data;
using AspNetCrud.Services;
using Microsoft.EntityFrameworkCore;
using Npgsql;

var builder = WebApplication.CreateBuilder(args);

// Конфигурация для Docker
builder.Configuration.AddJsonFile("appsettings.Docker.json", optional: true);

// Добавляем логирование
builder.Logging.ClearProviders();
builder.Logging.AddConsole();
builder.Logging.AddDebug();

// Регистрация сервисов
builder.Services.AddScoped<DockerService>();
builder.Services.AddSingleton<ITaskService, TaskService>();

// DbContext
builder.Services.AddDbContext<ApplicationDbContext>(options =>
    options.UseNpgsql(builder.Configuration.GetConnectionString("DefaultConnection")));

// Остальные сервисы
builder.Services.AddControllers();
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Middleware
app.UseSwagger();
app.UseSwaggerUI();
app.UseHttpsRedirection();
app.UseAuthorization();
app.MapControllers();
app.MapGet("/health", () => "Healthy");

// Инициализация БД
try
{
    using var scope = app.Services.CreateScope();
    var services = scope.ServiceProvider;
    var logger = services.GetRequiredService<ILogger<Program>>();
    var context = services.GetRequiredService<ApplicationDbContext>();
    
    // Ожидание готовности БД
    int retries = 10;
    while (retries-- > 0)
    {
        try
        {
            logger.LogInformation("Checking database connection...");
            context.Database.CanConnect();
            logger.LogInformation("Database is ready!");
            break;
        }
        catch (Exception ex)
        {
            logger.LogWarning($"Database not ready yet. {ex.Message}");
            await Task.Delay(5000);
        }
    }
    
    // Применение миграций
    logger.LogInformation("Applying database migrations...");
    context.Database.Migrate();
    logger.LogInformation("Migrations applied successfully");
}
catch (Exception ex)
{
    app.Logger.LogError(ex, "Error initializing database");
}

app.Run();