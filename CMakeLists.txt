cmake_minimum_required(VERSION 3.28.3)
project(cdb VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Automatically collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(cdb ${SOURCES})
