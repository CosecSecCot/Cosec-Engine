#pragma once

#include "Event.h"

#include <sstream>

namespace TopDown {

class TOPDOWN_API KeyEvent : public Event {
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)

    [[nodiscard]] int GetKeyCode() const { return m_KeyCode; }

protected:
    // Should not be able to construct KeyEvent directly.
    // It must be called from classes that derive from it.
    explicit KeyEvent(int keycode) : m_KeyCode(keycode) {}

    int m_KeyCode;
};

class TOPDOWN_API KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

    DECLARE_EVENT_TYPE(KeyPressed);

    [[nodiscard]] int GetRepeatCount() const { return m_RepeatCount; }

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << "repeats)";
        return ss.str();
    }

protected:
    int m_RepeatCount;
};

class TOPDOWN_API KeyReleasedEvent : public KeyEvent {
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

    DECLARE_EVENT_TYPE(KeyReleased);

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }
};

} // namespace TopDown
