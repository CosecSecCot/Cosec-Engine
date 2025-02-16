#pragma once

#include "CosecEngine/Core.h"
#include "CosecEngine/Log.h"

#include <pch.h>

namespace Cosec {

enum class EventType : std::uint8_t {
    None = 0,

    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,

    AppTick,
    AppUpdate,
    AppRender,

    KeyPressed,
    KeyReleased,

    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

enum class EventCategory : std::uint8_t {
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4),

};

inline EventCategory operator|(EventCategory lhs, EventCategory rhs) {
    return static_cast<EventCategory>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

inline EventCategory &operator|=(EventCategory &lhs, EventCategory rhs) {
    lhs = lhs | rhs;
    return lhs;
}

class COSEC_API Event {
    friend class EventDispatcher;

public:
    [[nodiscard]] virtual EventType GetEventType() const = 0;
    [[nodiscard]] virtual const char *GetName() const = 0;
    [[nodiscard]] virtual int GetCategoryFlags() const = 0;
    [[nodiscard]] virtual std::string ToString() const { return GetName(); }

    [[nodiscard]] bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & (int)category; }

protected:
    bool m_Handled = false;
};

#define DECLARE_EVENT_TYPE(type)                                                                                       \
    static EventType GetStaticType() { return EventType::type; }                                                       \
    [[nodiscard]] EventType GetEventType() const override { return GetStaticType(); }                                  \
    [[nodiscard]] const char *GetName() const override { return #type; }

#define DECLARE_EVENT_CATEGORY(category)                                                                               \
    [[nodiscard]] int GetCategoryFlags() const override { return static_cast<int>(category); }

class EventDispatcher {
    template <typename T> using EventFn = std::function<bool(T &)>;

public:
    EventDispatcher(Event &event) : m_Event(event) {}

    template <typename T> bool Dispatch(EventFn<T> func) {
        if (!std::is_base_of_v<Event, T>) {
            LOG_CORE_CRIT("Called Dispatch for a non-Event type!");
        }

        if (m_Event.GetEventType() == T::GetStaticType()) {
            // converting m_Event to the specific event type and
            // passing that to func, func will be handling that event.
            m_Event.m_Handled = func(static_cast<T &>(m_Event));
            return true;
        }

        return false;
    }

private:
    Event &m_Event;
};

} // namespace Cosec
