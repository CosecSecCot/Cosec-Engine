#pragma once

#include "Application.h"
#include "Log.h"

// clang-format off

#ifdef COSEC_WIN

int main(int argc, char **argv) {
    auto app = Cosec::CreateApplication();
    app->Run();
    delete app;
}

#elif COSEC_UNIX

int main(int argc, char **argv) {
    Cosec::Log::Init();
    LOG_CORE_WARN("Initialized Logger!");
    LOG_INFO("Hello from client!");

    auto app = Cosec::CreateApplication();
    app->Run();
    delete app;
}

#else
    #error "Platform not supported"
#endif

// clang-format on
