#pragma once

#include "CosecEngine/Renderer/GraphicsContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Cosec {

class OpenGLContext : public GraphicsContext {
public:
    explicit OpenGLContext(GLFWwindow *windowHandle);
    ~OpenGLContext() override = default;

    void Init() override;
    void SwapBuffers() override;

private:
    GLFWwindow *m_WindowHandle;
};

} // namespace Cosec
