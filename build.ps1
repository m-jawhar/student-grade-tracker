# Build script for Student Grade Tracker
# Usage: .\build.ps1 [clean|run|rebuild|help]

param(
    [string]$Target = "all"
)

$SRC_DIR = "src"
$BUILD_DIR = "build"
$BIN_DIR = "bin"
$DATA_DIR = "data"
$INCLUDE_DIR = "include"
$TARGET_EXE = "$BIN_DIR/studentSystem.exe"

$CFLAGS = "-Wall -Wextra -I$INCLUDE_DIR"
$CC = "gcc"

function Create-Directories {
    Write-Host "Creating directories..." -ForegroundColor Cyan
    if (!(Test-Path $BUILD_DIR)) { New-Item -ItemType Directory -Path $BUILD_DIR | Out-Null }
    if (!(Test-Path $BIN_DIR)) { New-Item -ItemType Directory -Path $BIN_DIR | Out-Null }
    if (!(Test-Path $DATA_DIR)) { New-Item -ItemType Directory -Path $DATA_DIR | Out-Null }
}

function Build-Project {
    Write-Host "Building Student Grade Tracker..." -ForegroundColor Green

    Create-Directories

    # Compile source files
    $sources = @("main", "grading", "fileio", "display", "operations", "statistics")

    foreach ($src in $sources) {
        Write-Host "  Compiling $src.c..." -ForegroundColor Yellow
        & $CC $CFLAGS.Split() -c "$SRC_DIR/$src.c" -o "$BUILD_DIR/$src.o"
        if ($LASTEXITCODE -ne 0) {
            Write-Host "Error compiling $src.c" -ForegroundColor Red
            exit 1
        }
    }

    # Link
    Write-Host "  Linking..." -ForegroundColor Yellow
    $objects = $sources | ForEach-Object { "$BUILD_DIR/$_.o" }
    & $CC $objects -o $TARGET_EXE

    if ($LASTEXITCODE -eq 0) {
        Write-Host "Build complete: $TARGET_EXE" -ForegroundColor Green
    } else {
        Write-Host "Error linking" -ForegroundColor Red
        exit 1
    }
}

function Clean-Build {
    Write-Host "Cleaning build artifacts..." -ForegroundColor Cyan
    if (Test-Path $BUILD_DIR) { Remove-Item -Recurse -Force $BUILD_DIR }
    if (Test-Path $BIN_DIR) { Remove-Item -Recurse -Force $BIN_DIR }
    Write-Host "Clean complete" -ForegroundColor Green
}

function Run-Program {
    if (!(Test-Path $TARGET_EXE)) {
        Write-Host "Executable not found. Building first..." -ForegroundColor Yellow
        Build-Project
    }
    Write-Host "Running Student Grade Tracker..." -ForegroundColor Green
    & $TARGET_EXE
}

function Show-Help {
    Write-Host "Student Grade Tracker - Build Script" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Usage: .\build.ps1 [target]" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Targets:" -ForegroundColor White
    Write-Host "  all      - Build the project (default)"
    Write-Host "  run      - Build and run the program"
    Write-Host "  clean    - Remove build artifacts"
    Write-Host "  rebuild  - Clean and rebuild"
    Write-Host "  help     - Show this help message"
}

# Main execution
switch ($Target.ToLower()) {
    "all" { Build-Project }
    "build" { Build-Project }
    "run" { Run-Program }
    "clean" { Clean-Build }
    "rebuild" { Clean-Build; Build-Project }
    "help" { Show-Help }
    default {
        Write-Host "Unknown target: $Target" -ForegroundColor Red
        Show-Help
        exit 1
    }
}
