cmake_minimum_required(VERSION 3.20)
project(glad LANGUAGES C)

# Create the glad shared library
add_library(glad SHARED src/glad.c)

# Set include directories properly
target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>   # For builds
    $<INSTALL_INTERFACE:include>  # For installed targets
)

# Set output directories
set_target_properties(glad PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/Glad
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/Glad
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/Glad
)

# Install target and export glad
install(TARGETS glad EXPORT GladConfig DESTINATION lib)
install(EXPORT GladConfig DESTINATION lib/cmake/glad)

# Install headers correctly
install(DIRECTORY include/ DESTINATION include)
