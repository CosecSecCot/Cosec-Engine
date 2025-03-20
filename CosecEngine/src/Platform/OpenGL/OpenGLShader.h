#pragma once

#include "CosecEngine/Renderer/Shader.h"
#include <pch.h>

namespace Cosec {

class OpenGLShader : public Shader {
public:
    OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource);
    ~OpenGLShader() override;

    void Bind() const override;
    void Unbind() const override;

private:
    uint32_t m_RendererID;
};

} // namespace Cosec
