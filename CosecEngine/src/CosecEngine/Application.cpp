#include "Application.h"
#include "CosecEngine/EngineWindow.h"

#include <glad/glad.h>

namespace Cosec {

Application *Application::s_Instance = nullptr;

Application::Application() {
    COSEC_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<EngineWindow>(EngineWindow::Create());
    m_Window->SetEventCallback([this](auto &&e) { Application::OnEvent(std::forward<decltype(e)>(e)); });
}
Application::~Application() = default;

void Application::OnEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(DISPATCH_EVENT_FN(Application::OnWindowClose));

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
        glad_glClearColor(0.07, 0.07, 0.08, 1);
        glad_glClear(GL_COLOR_BUFFER_BIT);

        for (const auto layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent &) {
    LOG_CORE_TRACE("Window Closed!");
    m_Running = false;
    return true;
}

} // namespace Cosec
