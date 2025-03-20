#include "OpenGLContext.h"
#include "CosecEngine/Core.h"
#include "CosecEngine/Log.h"

#include <glad/glad.h>

namespace Cosec {

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle) {
    COSEC_CORE_ASSERT(windowHandle != nullptr, "Window Handle cannot be nullptr");
}

void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);
    const int gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    COSEC_CORE_ASSERT(gladStatus, "Glad not initialized!");

    LOG_CORE_INFO("OpenGL Info:");
    LOG_CORE_INFO("\tVendor: {0}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    LOG_CORE_INFO("\tRenderer: {0}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    LOG_CORE_INFO("\tVersion: {0}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

} // namespace Cosec
