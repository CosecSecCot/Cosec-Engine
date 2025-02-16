#pragma once

#include "Event.h"

namespace Cosec {

class COSEC_API KeyEvent : public Event {
public:
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)

    [[nodiscard]] int GetKeyCode() const { return m_KeyCode; }

protected:
    // Should not be able to construct KeyEvent directly.
    // It must be called from classes that derive from it.
    explicit KeyEvent(int keycode) : m_KeyCode(keycode) {}

    int m_KeyCode;
};

class COSEC_API KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keycode, bool isRepeat = false) : KeyEvent(keycode), m_IsRepeat(isRepeat) {}

    DECLARE_EVENT_TYPE(KeyPressed);

    [[nodiscard]] bool IsRepeat() const { return m_IsRepeat; }

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << " (repeat=" << m_IsRepeat << ")";
        return ss.str();
    }

protected:
    bool m_IsRepeat;
};

class COSEC_API KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

    DECLARE_EVENT_TYPE(KeyReleased);

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }
};

} // namespace Cosec
