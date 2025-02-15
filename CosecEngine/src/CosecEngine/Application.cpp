#include "Application.h"
#include "CosecEngine/EngineWindow.h"

namespace Cosec {

Application::Application() { m_Window = std::unique_ptr<EngineWindow>(EngineWindow::Create()); }
Application::~Application() = default;

void Application::Run() {
    while (m_Running) {
        m_Window->OnUpdate();
    }
}

} // namespace Cosec
