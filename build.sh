#!/bin/bash

# Set build directory
BUILD_DIR="build"

# Clean build directory if "clean" command is passed
if [ "$1" = "clean" ]; then
    rm -rf build
fi

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Navigate to build directory
cd "$BUILD_DIR"

# Run CMake to generate the build system
cmake ..

# Build the project
cmake --build .
