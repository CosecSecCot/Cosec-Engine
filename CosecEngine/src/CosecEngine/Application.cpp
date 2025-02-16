#include "Application.h"
#include "CosecEngine/EngineWindow.h"

namespace Cosec {

Application::Application() {
    m_Window = std::unique_ptr<EngineWindow>(EngineWindow::Create());
    m_Window->SetEventCallback([this](auto &&e) { Application::OnEvent(std::forward<decltype(e)>(e)); });
}
Application::~Application() = default;

void Application::OnEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(
        [this](auto &&e) -> bool { return OnWindowClose(std::forward<decltype(e)>(e)); });

    LOG_CORE_TRACE("{0}", e.ToString());
}

void Application::Run() {
    while (m_Running) {
        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
    m_Running = false;
    return true;
}

} // namespace Cosec
