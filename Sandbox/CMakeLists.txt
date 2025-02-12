cmake_minimum_required(VERSION 3.20)
project(Sandbox)

# Create the Sandbox executable
add_executable(Sandbox)

target_sources(Sandbox PRIVATE
    src/Application.cpp  # Add actual source files here
)
target_include_directories(Sandbox PUBLIC
    ${CMAKE_SOURCE_DIR}/TopDownEngine/src
    ${CMAKE_SOURCE_DIR}/TopDownEngine/vendor/spdlog/include
)

# Link TopDownEngine to Sandbox
target_link_libraries(Sandbox PRIVATE TopDownEngine)

# Set output directories for Sandbox
set_target_properties(Sandbox PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/Sandbox
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/Sandbox
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/Sandbox
)

# Set C++ standard
set_property(TARGET Sandbox PROPERTY CXX_STANDARD 17)
