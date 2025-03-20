#pragma once

#include "Shader.h"
#include "CosecEngine/Core.h"
#include "CosecEngine/Log.h"
#include "CosecEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Cosec {

Shader *Shader::Create(const std::string &vertexSource, const std::string &fragmentSource) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::NONE:
        COSEC_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!")
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGLShader(vertexSource, fragmentSource);
    }

    COSEC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Cosec
