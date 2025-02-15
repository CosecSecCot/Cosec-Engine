#pragma once

#include "Event.h"

namespace Cosec {

class COSEC_API MouseMovedEvent : public Event {
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

    DECLARE_EVENT_TYPE(MouseMoved);
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);

    [[nodiscard]] float GetX() const { return m_MouseX; }
    [[nodiscard]] float GetY() const { return m_MouseY; }

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

private:
    float m_MouseX, m_MouseY;
};

class COSEC_API MouseScrolledEvent : public Event {
    MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

    DECLARE_EVENT_TYPE(MouseScrolled);
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);

    [[nodiscard]] float GetXOffset() const { return m_XOffset; }
    [[nodiscard]] float GetYOffset() const { return m_YOffset; }

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
        return ss.str();
    }

private:
    float m_XOffset, m_YOffset;
};

class COSEC_API MouseButtonEvent : public Event {
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);

    [[nodiscard]] int GetMouseButton() const { return m_Button; }

protected:
    MouseButtonEvent(int button) : m_Button(button) {}
    int m_Button;
};

class COSEC_API MouseButtonPressedEvent : public MouseButtonEvent {
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

    DECLARE_EVENT_TYPE(MouseButtonPressed);

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }
};

class COSEC_API MouseButtonReleasedEvent : public MouseButtonEvent {
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    DECLARE_EVENT_TYPE(MouseButtonReleased);

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }
};

} // namespace Cosec
