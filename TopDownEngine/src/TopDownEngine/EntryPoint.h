#pragma once

#include "Application.h"
#include "Log.h"

// clang-format off

#ifdef TOPDOWN_WIN

int main(int argc, char **argv) {
    auto app = TopDown::CreateApplication();
    app->Run();
    delete app;
}

#elif TOPDOWN_UNIX

int main(int argc, char **argv) {
    TopDown::Log::Init();
    LOG_CORE_WARN("Initialized Logger!");
    LOG_INFO("Hello from client!");

    auto app = TopDown::CreateApplication();
    app->Run();
    delete app;
}

#else
    #error "Platform not supported"
#endif

// clang-format on
