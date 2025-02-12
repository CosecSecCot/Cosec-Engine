#pragma once

// clang-format off

#ifdef TOPDOWN_WIN
    #ifdef TOPDOWN_BUILD_DLL
        #define TOPDOWN_API __declspec(dllexport)
    #else
        #define TOPDOWN_API __declspec(dllimport)
    #endif
#elif TOPDOWN_UNIX
    #ifdef TOPDOWN_BUILD_DLL
        #define TOPDOWN_API __attribute__((visibility("default")))
    #else
        #define TOPDOWN_API
    #endif
#else
    #error "Platform not supported!"
#endif

// clang-format on
