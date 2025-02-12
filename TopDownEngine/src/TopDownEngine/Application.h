#pragma once

#include "Core.h"

namespace TopDown {

class TOPDOWN_API Application {
public:
    Application();
    virtual ~Application();

    void Run();
};

// To be defined in client
extern Application *CreateApplication();

} // namespace TopDown
