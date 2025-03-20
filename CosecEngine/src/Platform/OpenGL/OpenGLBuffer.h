#pragma once

#include "CosecEngine/Renderer/Buffer.h"

#include <glad/glad.h>

namespace Cosec {

// =============
// Vertex Buffer
// =============

class OpenGLVertexBuffer : public VertexBuffer {
public:
    OpenGLVertexBuffer(float *vertices, uint32_t size);
    ~OpenGLVertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;
    void SetLayout(const BufferLayout &layout) override { m_Layout = layout; }
    const BufferLayout &GetLayout() override { return m_Layout; }

private:
    GLuint m_RendererID;
    BufferLayout m_Layout;
};

// ============
// Index Buffer
// ============

class OpenGLIndexBuffer : public IndexBuffer {
public:
    OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
    ~OpenGLIndexBuffer() override;

    void Bind() const override;
    void Unbind() const override;
    [[nodiscard]] uint32_t GetCount() const override { return m_Count; };

private:
    GLuint m_RendererID;
    uint32_t m_Count;
};

} // namespace Cosec
