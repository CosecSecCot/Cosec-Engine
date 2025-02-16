#include "UnixWindow.h"
#include "CosecEngine/Core.h"
#include "CosecEngine/Events/ApplicationEvent.h"
#include "CosecEngine/Events/KeyEvent.h"
#include "CosecEngine/Events/MouseEvent.h"
#include "CosecEngine/Log.h"

#include <GLFW/glfw3.h>

namespace Cosec {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description) {
    LOG_CORE_ERROR("GLFW Error {0}: {1}", error, description);
}

EngineWindow *EngineWindow::Create(const WindowProps &props) { return new UnixWindow(props); }

UnixWindow::UnixWindow(const WindowProps &props) { Init(props); }

UnixWindow::~UnixWindow() { Shutdown(); }

void UnixWindow::Init(const WindowProps &props) {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    LOG_CORE_INFO("Creating Window \"{0}\"({1}x{2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized) {
        int success = glfwInit();
        COSEC_CORE_ASSERT(success, "GLFW not initialized!");

        glfwSetErrorCallback(GLFWErrorCallback);

        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), props.Title.c_str(),
                                nullptr, nullptr);

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    /*
     * GLFW Event Callbacks
     */

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
        WindowData &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        WindowData &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        switch (action) {
        case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            data.EventCallback(event);
            break;
        }
        default:
            break;
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        switch (action) {
        case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            data.EventCallback(event);
            break;
        }
        default:
            break;
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
        WindowData &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(window));

        MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
        data.EventCallback(event);
    });
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
