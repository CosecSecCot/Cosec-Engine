#define GLFW_INCLUDE_NONE
#include "ImGuiLayer.h"

#include "CosecEngine/Application.h"
#include "CosecEngine/Events/KeyEvent.h"
#include "CosecEngine/Events/MouseEvent.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <pch.h>

namespace Cosec {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

ImGuiLayer::~ImGuiLayer() = default;

void ImGuiLayer::OnAttach() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO &io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplOpenGL3_Init();
}

void ImGuiLayer::OnDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::OnUpdate() {
    // (Your code calls glfwPollEvents())
    // ...
    // Start the Dear ImGui frame
    ImGuiIO &io = ImGui::GetIO();
    auto time = static_cast<float>(glfwGetTime());
    io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);

    Application &app = Application::Get();

    io.DisplaySize =
        ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show); // Show demo window! :)
    // Rendering
    // (Your code clears your framebuffer, renders your other stuff etc.)
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // (Your code calls glfwSwapBuffers() etc.)
}

void ImGuiLayer::OnEvent(Event &event) {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(DISPATCH_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    dispatcher.Dispatch<KeyPressedEvent>(DISPATCH_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(DISPATCH_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(DISPATCH_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(DISPATCH_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(DISPATCH_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(DISPATCH_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &e) {
    auto &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glad_glViewport(0, 0, static_cast<int>(e.GetWidth()), static_cast<int>(e.GetHeight()));

    return false;
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e) {
    LOG_CORE_ERROR("ImGui Key Pressed Event not implemented yet!");
    return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e) {
    LOG_CORE_ERROR("ImGui Key Released Event not implemented yet!");
    return false;
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &e) {
    ImGui::GetIO().AddMouseButtonEvent(e.GetMouseButton(), true);
    return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e) {
    ImGui::GetIO().AddMouseButtonEvent(e.GetMouseButton(), false);
    return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e) {
    ImGui::GetIO().AddMousePosEvent(e.GetX(), e.GetY());
    return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e) {
    ImGui::GetIO().AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
    return false;
}

} // namespace Cosec
