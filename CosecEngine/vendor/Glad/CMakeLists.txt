cmake_minimum_required(VERSION 3.20)
project(glad LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -fPIC")

# Create the glad static library
add_library(glad STATIC src/glad.c)

# Set include directories
target_include_directories(glad PUBLIC
    include/
)
