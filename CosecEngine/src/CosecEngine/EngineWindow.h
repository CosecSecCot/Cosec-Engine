#pragma once

#include "Core.h"
#include "CosecEngine/Events/Event.h"

#include <pch.h>

namespace Cosec {

struct WindowProps {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(std::string title = "Cosec Engine", unsigned int width = 1280, unsigned int height = 720)
        : Title(std::move(title)), Width(width), Height(height) {}
};

class COSEC_API EngineWindow {
public:
    using EventCallbackFn = std::function<bool(Event &)>;

    virtual ~EngineWindow() = default;

    virtual void OnUpdate() = 0;
    [[nodiscard]] virtual unsigned int GetWidth() const = 0;
    [[nodiscard]] virtual unsigned int GetHeight() const = 0;
    virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    [[nodiscard]] virtual bool IsVSync() const = 0;

    static EngineWindow *Create(const WindowProps &props = WindowProps());
};

} // namespace Cosec
