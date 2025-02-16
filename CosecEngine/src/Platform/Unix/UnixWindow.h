#pragma once

#include "CosecEngine/EngineWindow.h"

#include <GLFW/glfw3.h>

namespace Cosec {

class UnixWindow : public EngineWindow {
public:
    explicit UnixWindow(const WindowProps &props);
    ~UnixWindow() override;

    void OnUpdate() override;

    [[nodiscard]] uint32_t GetWidth() const override { return m_Data.Width; }
    [[nodiscard]] uint32_t GetHeight() const override { return m_Data.Height; }

    void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    [[nodiscard]] bool IsVSync() const override;

private:
    virtual void Init(const WindowProps &props);
    virtual void Shutdown();

    GLFWwindow *m_Window;

    struct WindowData {
        std::string Title;
        uint32_t Width, Height;
        bool VSync;
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};

} // namespace Cosec
