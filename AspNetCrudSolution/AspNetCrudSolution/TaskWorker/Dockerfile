FROM mcr.microsoft.com/dotnet/runtime:8.0 AS base
WORKDIR /app

FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build
WORKDIR /src
COPY ["TaskWorker/TaskWorker.csproj", "TaskWorker/"]
RUN dotnet restore "TaskWorker/TaskWorker.csproj"
COPY . .
RUN dotnet build "TaskWorker/TaskWorker.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "TaskWorker/TaskWorker.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "TaskWorker.dll"]