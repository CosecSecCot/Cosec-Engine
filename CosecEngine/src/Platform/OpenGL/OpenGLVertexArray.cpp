#pragma once

#include "OpenGLVertexArray.h"

namespace Cosec {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
        return GL_INT;
    case ShaderDataType::Bool:
        return GL_BOOL;
    case ShaderDataType::None:
        break;
    }

    COSEC_CORE_ASSERT(false, "Unkown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray() : m_RendererID(0) {
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &m_RendererID); }

void OpenGLVertexArray::Bind() const { glBindVertexArray(m_RendererID); }

void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
    COSEC_CORE_ASSERT(!vertexBuffer->GetLayout().GetElements().empty(), "VertexBuffer has no layout!");

    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    uint32_t attribIndex = 0;
    const auto &layout = vertexBuffer->GetLayout();
    for (const auto &element : layout) {
        glEnableVertexAttribArray(attribIndex);
        glVertexAttribPointer(attribIndex, element.GetElementCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                              reinterpret_cast<const void *>(element.Offset));
        attribIndex++;
    }
    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}

} // namespace Cosec
