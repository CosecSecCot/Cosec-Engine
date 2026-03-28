cmake_minimum_required(VERSION 3.20)

project(CosecEngine)

# User option to select Wayland or X11
option(USE_WAYLAND "Build with Wayland support instead of X11" OFF)
option(COSEC_SHARED "Build CosecEngine as a shared library" OFF)

if (USE_WAYLAND)
    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
    set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
else()
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
endif()

# Define the CosecEngine library
# add_library(CosecEngine SHARED)
if (COSEC_SHARED)
    add_library(CosecEngine SHARED)
else()
    add_library(CosecEngine STATIC)
endif()
target_sources(CosecEngine PRIVATE
    src/pch.cpp
    src/CosecEngine/Application.cpp
    src/CosecEngine/Log.cpp
    src/CosecEngine/Layer.cpp
    src/CosecEngine/LayerStack.cpp
    src/CosecEngine/ImGui/ImGuiLayer.cpp
    src/CosecEngine/Renderer/Buffer.cpp
    src/CosecEngine/Renderer/Renderer.cpp
    src/CosecEngine/Renderer/Shader.cpp
    src/CosecEngine/Renderer/VertexArray.cpp
    src/Platform/OpenGL/OpenGLContext.cpp
    src/Platform/OpenGL/OpenGLBuffer.cpp
    src/Platform/OpenGL/OpenGLShader.cpp
    src/Platform/OpenGL/OpenGLVertexArray.cpp
    src/Platform/Unix/UnixWindow.cpp
    src/Platform/Unix/UnixInput.cpp
)

target_precompile_headers(CosecEngine PRIVATE src/pch.h)

if (COSEC_SHARED)
    target_compile_definitions(CosecEngine PRIVATE COSEC_BUILD_DLL)
    target_compile_definitions(CosecEngine PRIVATE IMGUI_USER_CONFIG="${CMAKE_CURRENT_SOURCE_DIR}/src/CosecEngine/Core.h")
endif()

# External libraries
target_include_directories(CosecEngine PRIVATE
    src
    vendor/spdlog/include
    vendor/GLFW/include
    vendor/Glad/include
    vendor/ImGui
    vendor/ImGui/backends
    vendor/GLM
)

# Compile ImGui with CosecEngine
target_sources(CosecEngine PRIVATE
    vendor/ImGui/imconfig.h
    vendor/ImGui/imgui.cpp
    vendor/ImGui/imgui.h
    vendor/ImGui/imgui_demo.cpp
    vendor/ImGui/imgui_draw.cpp
    vendor/ImGui/imgui_internal.h
    vendor/ImGui/imgui_tables.cpp
    vendor/ImGui/imgui_widgets.cpp
    vendor/ImGui/imstb_rectpack.h
    vendor/ImGui/imstb_textedit.h
    vendor/ImGui/imstb_truetype.h
    vendor/ImGui/backends/imgui_impl_opengl3.cpp
    vendor/ImGui/backends/imgui_impl_opengl3.h
    vendor/ImGui/backends/imgui_impl_glfw.cpp
    vendor/ImGui/backends/imgui_impl_glfw.h
)

# Link GLFW and OpenGL
add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/Glad)
add_subdirectory(vendor/GLM)
find_package(OpenGL REQUIRED)
target_link_libraries(CosecEngine PRIVATE spdlog::spdlog glm glad glfw OpenGL::GL)

if (COSEC_SHARED)
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

    if (WIN32)
        add_custom_command(TARGET CosecEngine POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "$<TARGET_FILE:CosecEngine>"
                "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/Sandbox/$<TARGET_FILE_NAME:CosecEngine>"
        )
    endif()
endif()
