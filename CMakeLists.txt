cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(topDownGame VERSION 1.0.0)

include(FetchContent)

function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG        ${gitTag}
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# SDL2
include_dependency(SDL2 https://github.com/libsdl-org/SDL release-2.30.8)

# SDL2_image
include_dependency(SDL2_image https://github.com/libsdl-org/SDL_image release-2.8.2)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(topDownGame main.cpp ${SRC_FILES})
target_include_directories(topDownGame PRIVATE src)

target_include_directories(
    topDownGame
    PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(
    topDownGame
    PRIVATE
    SDL2
    SDL2main
    SDL2_image
)

if (WIN32)
    add_custom_command(
            TARGET topDownGame POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:topDownGame>"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2_image::SDL2_image>" "$<TARGET_FILE_DIR:topDownGame>"
            VERBATIM
    )
endif()

