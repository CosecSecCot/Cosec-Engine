#pragma once

#include "CosecEngine/Events/ApplicationEvent.h"
#include "CosecEngine/Events/KeyEvent.h"
#include "CosecEngine/Events/MouseEvent.h"
#include "CosecEngine/Layer.h"

namespace Cosec {

class ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnEvent(Event &event) override;

private:
    static bool OnWindowResizeEvent(WindowResizeEvent &e);
    static bool OnKeyPressedEvent(KeyPressedEvent &e);
    static bool OnKeyReleasedEvent(KeyReleasedEvent &e);
    static bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &e);
    static bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
    static bool OnMouseMovedEvent(MouseMovedEvent &e);
    static bool OnMouseScrolledEvent(MouseScrolledEvent &e);

    float m_Time = 0.0f;
};

} // namespace Cosec
