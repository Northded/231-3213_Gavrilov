FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS base
WORKDIR /app
EXPOSE 5171
ENV ASPNETCORE_URLS=http://*:5171

FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build
WORKDIR /src
COPY ["AspNetCrud/AspNetCrud.csproj", "AspNetCrud/"]
RUN dotnet restore "AspNetCrud/AspNetCrud.csproj"
COPY . .
RUN dotnet build "AspNetCrud/AspNetCrud.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "AspNetCrud/AspNetCrud.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "AspNetCrud.dll"]