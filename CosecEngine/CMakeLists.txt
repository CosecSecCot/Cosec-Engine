cmake_minimum_required(VERSION 3.20)

project(CosecEngine)

# User option to select Wayland or X11
option(USE_WAYLAND "Build with Wayland support instead of X11" OFF)

if (USE_WAYLAND)
    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
    set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
else()
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
endif()

# Define the CosecEngine library
add_library(CosecEngine SHARED)
target_sources(CosecEngine PRIVATE
    src/pch.cpp
    src/CosecEngine/Application.cpp
    src/CosecEngine/Log.cpp
    src/Platform/Unix/UnixWindow.cpp
)
target_compile_definitions(CosecEngine PRIVATE COSEC_BUILD_DLL)

target_precompile_headers(CosecEngine PRIVATE src/pch.h)

# External libraries
target_include_directories(CosecEngine PRIVATE
    src
    vendor/spdlog/include
    vendor/GLFW/include
)

# Link GLFW and OpenGL
add_subdirectory(vendor/GLFW)
find_package(OpenGL REQUIRED)
target_link_libraries(CosecEngine PRIVATE glfw OpenGL::GL)

# Set output directories for different configurations
set_target_properties(CosecEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/CosecEngine
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/CosecEngine
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/CosecEngine
)

# Export the library
install(TARGETS CosecEngine EXPORT CosecEngineConfig DESTINATION lib)
install(EXPORT CosecEngineConfig DESTINATION lib/cmake/CosecEngine)
install(DIRECTORY src/ DESTINATION include)

# Set C++ standard
set_property(TARGET CosecEngine PROPERTY CXX_STANDARD 17)
