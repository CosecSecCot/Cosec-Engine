#include "Application.h"
#include "Events/ApplicationEvent.h"

namespace TopDown {

Application::Application() = default;
Application::~Application() = default;

void Application::Run() {
    WindowResizeEvent e(1280, 720);
    LOG_TRACE(e.ToString());

    while (true)
        ;
}

} // namespace TopDown
