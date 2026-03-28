#include "VertexArray.h"
#include "CosecEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Cosec {

VertexArray *VertexArray::Create() {
    switch (Renderer::GetAPI()) {
    case RendererAPI::NONE:
        COSEC_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!")
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexArray();
    }

    COSEC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Cosec
