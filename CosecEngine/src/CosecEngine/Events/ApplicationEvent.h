#pragma once

#include "Event.h"

namespace Cosec {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}

    DECLARE_EVENT_TYPE(WindowResize);
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryApplication);

    [[nodiscard]] uint32_t GetWidth() const { return m_Width; }
    [[nodiscard]] uint32_t GetHeight() const { return m_Height; }

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << "x" << m_Height;
        return ss.str();
    }

private:
    uint32_t m_Width, m_Height;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    DECLARE_EVENT_TYPE(WindowClose)
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryApplication)
};

class AppTickEvent : public Event {
public:
    AppTickEvent() = default;

    DECLARE_EVENT_TYPE(AppTick)
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryApplication)
};

class AppUpdateEvent : public Event {
public:
    AppUpdateEvent() = default;

    DECLARE_EVENT_TYPE(AppUpdate)
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryApplication)
};

class AppRenderEvent : public Event {
public:
    AppRenderEvent() = default;

    DECLARE_EVENT_TYPE(AppRender)
    DECLARE_EVENT_CATEGORY(EventCategory::EventCategoryApplication)
};

} // namespace Cosec
