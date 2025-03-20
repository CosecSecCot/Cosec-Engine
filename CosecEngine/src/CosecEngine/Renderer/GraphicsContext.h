#pragma once

namespace Cosec {

class GraphicsContext {
public:
    GraphicsContext() = default;
    virtual ~GraphicsContext() = default;

    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};

} // namespace Cosec
