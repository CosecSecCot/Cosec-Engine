#pragma once

namespace Cosec {

enum class RendererAPI {
    NONE = 0,
    OpenGL = 1,
};

class Renderer {
public:
    static RendererAPI GetAPI() { return s_RendererAPI; }

private:
    static RendererAPI s_RendererAPI;
};

} // namespace Cosec
