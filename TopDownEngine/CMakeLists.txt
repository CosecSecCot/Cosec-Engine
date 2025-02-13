cmake_minimum_required(VERSION 3.20)

project(TopDownEngine)

# Define the TopDownEngine library
add_library(TopDownEngine SHARED)
target_sources(TopDownEngine PRIVATE
    src/pch.cpp
    src/TopDownEngine/Application.cpp
    src/TopDownEngine/Log.cpp
)
target_compile_definitions(TopDownEngine PRIVATE TOPDOWN_BUILD_DLL)

target_precompile_headers(TopDownEngine PRIVATE src/pch.h)

# External libraries
target_include_directories(TopDownEngine PRIVATE
    src
    vendor/spdlog/include
)

# Set output directories for different configurations
set_target_properties(TopDownEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/TopDownEngine
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/TopDownEngine
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/TopDownEngine
)

# Export the library
install(TARGETS TopDownEngine EXPORT TopDownEngineConfig DESTINATION lib)
install(EXPORT TopDownEngineConfig DESTINATION lib/cmake/TopDownEngine)
install(DIRECTORY src/ DESTINATION include)

# Set C++ standard
set_property(TARGET TopDownEngine PROPERTY CXX_STANDARD 17)
