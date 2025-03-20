#pragma once

#include <pch.h>

namespace Cosec {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static Shader *Create(const std::string &vertexSource, const std::string &fragmentSource);
};

} // namespace Cosec
