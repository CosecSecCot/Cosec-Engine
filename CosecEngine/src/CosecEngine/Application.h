#pragma once

#include "Core.h"
#include "CosecEngine/EngineWindow.h"
#include "CosecEngine/Events/ApplicationEvent.h"
#include "CosecEngine/Layer.h"
#include "CosecEngine/LayerStack.h"

#include <pch.h>

namespace Cosec {

class COSEC_API Application {
public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event &e);
    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);

private:
    bool OnWindowClose(WindowCloseEvent &e);

    std::unique_ptr<EngineWindow> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;
};

// To be defined in client
extern Application *CreateApplication();

} // namespace Cosec
