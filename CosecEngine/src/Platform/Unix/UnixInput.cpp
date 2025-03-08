#include "UnixInput.h"
#include "CosecEngine/Application.h"
#include "CosecEngine/Core.h"
#include "CosecEngine/EngineInput.h"

#include <GLFW/glfw3.h>
#include <pch.h>

namespace Cosec {

EngineInput *EngineInput::s_Instance = new UnixInput();

bool UnixInput::IsKeyPressedImpl(int keycode) {
    const auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    COSEC_CORE_ASSERT(window != nullptr, "Window is NULL!");

    const auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool UnixInput::IsMouseButtonPressedImpl(int button) {
    const auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    COSEC_CORE_ASSERT(window != nullptr, "Window is NULL!");

    const auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

float UnixInput::GetMouseXImpl() { return UnixInput::GetMousePosImpl().first; }

float UnixInput::GetMouseYImpl() { return UnixInput::GetMousePosImpl().second; }

std::pair<float, float> UnixInput::GetMousePosImpl() {
    const auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    COSEC_CORE_ASSERT(window != nullptr, "Window is NULL!");

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {static_cast<float>(xpos), static_cast<float>(ypos)};
}

} // namespace Cosec
