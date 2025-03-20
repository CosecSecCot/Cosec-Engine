#pragma once

#include "CosecEngine/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace Cosec {

class OpenGLVertexArray : public VertexArray {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;
    [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override {
        return m_VertexBuffers;
    }
    [[nodiscard]] const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override { return m_IndexBuffer; }

private:
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    GLuint m_RendererID;
};

} // namespace Cosec
