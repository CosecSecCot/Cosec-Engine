#include "UnixInput.h"
#include "CosecEngine/Application.h"
#include "CosecEngine/EngineInput.h"

#include <GLFW/glfw3.h>
#include <pch.h>

namespace Cosec {

EngineInput *EngineInput::s_Instance = new UnixInput();

bool UnixInput::IsKeyPressedImpl(int keycode) {
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);

    return state == GLFW_PRESS || GLFW_REPEAT;
}

bool UnixInput::IsMouseButtonPressedImpl(int button) {
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);

    return state == GLFW_PRESS;
}

float UnixInput::GetMouseXImpl() {
    auto [xpos, _] = UnixInput::GetMousePosImpl();
    return static_cast<float>(xpos);
}

float UnixInput::GetMouseYImpl() {
    auto [_, ypos] = UnixInput::GetMousePosImpl();
    return static_cast<float>(ypos);
}

std::pair<float, float> UnixInput::GetMousePosImpl() {
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {static_cast<float>(xpos), static_cast<float>(ypos)};
}

} // namespace Cosec
