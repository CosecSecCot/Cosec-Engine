#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace Cosec {

BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements) : m_Elements(elements), m_Stride(0) {
    CalculateOffsetAndStride();
}

void BufferLayout::CalculateOffsetAndStride() {
    uint32_t offset = 0;
    m_Stride = 0;
    for (auto &element : m_Elements) {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }
}

VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::NONE:
        COSEC_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!")
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
    }

    COSEC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t count) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::NONE:
        COSEC_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!")
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLIndexBuffer(indices, count);
    }

    COSEC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Cosec
