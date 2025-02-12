cmake_minimum_required(VERSION 3.20)

project(TopDownEngine)

# Define the TopDownEngine library
add_library(TopDownEngine SHARED)
target_sources(TopDownEngine PRIVATE
    src/TopDownEngine/Application.cpp  # Add actual source files here
)
target_compile_definitions(TopDownEngine PRIVATE TOPDOWN_BUILD_DLL)

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
