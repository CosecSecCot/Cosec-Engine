#pragma once

#include "Core.h"
#include "CosecEngine/EngineWindow.h"

#include <pch.h>

namespace Cosec {

class COSEC_API Application {
public:
    Application();
    virtual ~Application();

    void Run();

private:
    std::unique_ptr<EngineWindow> m_Window;
    bool m_Running = true;
};

// To be defined in client
extern Application *CreateApplication();

} // namespace Cosec
