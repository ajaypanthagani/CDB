@echo off

:: Set build directory
set BUILD_DIR=build

:: Create build directory if it doesn't exist
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

:: Navigate to build directory
cd "%BUILD_DIR%"

:: Run CMake to generate the build system
cmake ..

:: Build the project
cmake --build .
