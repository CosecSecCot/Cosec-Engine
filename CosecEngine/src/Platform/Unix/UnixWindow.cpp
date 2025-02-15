#include "UnixWindow.h"
#include "CosecEngine/Core.h"
#include "CosecEngine/Log.h"

#include <GLFW/glfw3.h>

namespace Cosec {

static bool s_GLFWInitialized = false;

EngineWindow *EngineWindow::Create(const WindowProps &props) { return new UnixWindow(props); }

UnixWindow::UnixWindow(const WindowProps &props) { Init(props); }

UnixWindow::~UnixWindow() { Shutdown(); }

void UnixWindow::Init(const WindowProps &props) {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    LOG_CORE_INFO("Creating Window \"{0}\", ({1}x{2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized) {
        int success = glfwInit();
        COSEC_CORE_ASSERT(success, "GLFW not initialized!");

        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), props.Title.c_str(),
                                nullptr, nullptr);

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
}

void UnixWindow::Shutdown() { glfwDestroyWindow(m_Window); }

void UnixWindow::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void UnixWindow::SetVSync(bool enabled) {
    if (enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

    m_Data.VSync = enabled;
}

bool UnixWindow::IsVSync() const { return m_Data.VSync; }

} // namespace Cosec
