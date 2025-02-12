#pragma once

#include "Application.h"

// clang-format off

#ifdef TOPDOWN_WIN

int main(int argc, char **argv) {
    auto app = TopDown::CreateApplication();
    app->Run();
    delete app;
}

#elif TOPDOWN_UNIX

int main(int argc, char **argv) {
    auto app = TopDown::CreateApplication();
    app->Run();
    delete app;
}

#else
    #error "Platform not supported"
#endif

// clang-format on
