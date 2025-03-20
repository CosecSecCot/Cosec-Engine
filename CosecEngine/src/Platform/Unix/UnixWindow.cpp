#include "Platform/OpenGL/OpenGLContext.h"
#define GLFW_INCLUDE_NONE
#include "CosecEngine/Core.h"
#include "CosecEngine/Events/ApplicationEvent.h"
#include "CosecEngine/Events/KeyEvent.h"
#include "CosecEngine/Events/MouseEvent.h"
#include "CosecEngine/Log.h"
#include "UnixWindow.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cosec {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description) {
    LOG_CORE_ERROR("GLFW Error {0}: {1}", error, description);
}

EngineWindow *EngineWindow::Create(const WindowProps &props) { return new UnixWindow(props); }

UnixWindow::UnixWindow(const WindowProps &props) : m_Window(nullptr), m_Context(nullptr) { UnixWindow::Init(props); }

UnixWindow::~UnixWindow() { UnixWindow::Shutdown(); }

void UnixWindow::Init(const WindowProps &props) {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    LOG_CORE_INFO("Creating Window \"{0}\"({1}x{2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized) {
        const int glfwStatus = glfwInit();
        COSEC_CORE_ASSERT(glfwStatus, "GLFW not initialized!");

        glfwSetErrorCallback(GLFWErrorCallback);

        s_GLFWInitialized = true;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), props.Title.c_str(),
                                nullptr, nullptr);

    m_Context = new OpenGLContext(m_Window);
    m_Context->Init();

    // glfwMakeContextCurrent(m_Window);
    // const int gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    // COSEC_CORE_ASSERT(gladStatus, "Glad not initialized!")

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
            KeyPressedEvent event(key, false);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, true);
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
    m_Context->SwapBuffers();
    // glfwSwapBuffers(m_Window);
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
