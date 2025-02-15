cmake_minimum_required(VERSION 3.20)

project(CosecEngineProject)

# Enable compile_commands.json for LSP support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define build configuration if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Detect platform and define appropriate macros
if(WIN32)
    add_compile_definitions(COSEC_WIN)
elseif(UNIX)
    add_compile_definitions(COSEC_UNIX)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Determine if x86 or x64 (only supporting x64)
if (CMAKE_SIZEOF_VOID_P GREATER 4)
    set(PLATFORM "x86_64")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Add subdirectories
add_subdirectory(CosecEngine)
add_subdirectory(Sandbox)
