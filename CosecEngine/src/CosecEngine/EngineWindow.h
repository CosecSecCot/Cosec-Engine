#pragma once

#include "Core.h"
#include "CosecEngine/Events/Event.h"

#include <pch.h>

namespace Cosec {

struct WindowProps {
    std::string Title;
    uint32_t Width;
    uint32_t Height;

    WindowProps(std::string title = "Cosec Engine", uint32_t width = 1280, uint32_t height = 720)
        : Title(std::move(title)), Width(width), Height(height) {}
};

class COSEC_API EngineWindow {
public:
    using EventCallbackFn = std::function<void(Event &)>;

    virtual ~EngineWindow() = default;

    virtual void OnUpdate() = 0;
    [[nodiscard]] virtual uint32_t GetWidth() const = 0;
    [[nodiscard]] virtual uint32_t GetHeight() const = 0;
    virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    [[nodiscard]] virtual bool IsVSync() const = 0;

    static EngineWindow *Create(const WindowProps &props = WindowProps());
};

} // namespace Cosec
