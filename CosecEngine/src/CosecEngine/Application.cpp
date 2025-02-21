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

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer *overlay) { m_LayerStack.PushOverlay(overlay); }

void Application::Run() {
    while (m_Running) {
        for (auto layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
    m_Running = false;
    return true;
}

} // namespace Cosec
