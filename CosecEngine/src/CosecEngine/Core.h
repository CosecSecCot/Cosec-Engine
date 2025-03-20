#pragma once

// clang-format off

#if COSEC_SHARED
    #if COSEC_WIN
        #ifdef COSEC_BUILD_DLL
            #define COSEC_API __declspec(dllexport)
            #define IMGUI_API __declspec(dllexport)
        #else
            #define COSEC_API __declspec(dllimport)
            #define IMGUI_API __declspec(dllimport)
        #endif
    #elif COSEC_UNIX
        #ifdef COSEC_BUILD_DLL
            #define COSEC_API __attribute__((visibility("default")))
            #define IMGUI_API __attribute__((visibility("default")))
        #else
            #define COSEC_API
        #endif
    #else
        #error "Platform not supported!"
    #endif
#else
    #if COSEC_WIN 
        #define COSEC_API
        #define IMGUI_API
    #elif COSEC_UNIX
        #define COSEC_API
        #define IMGUI_API
    #else
        #error "Platform not supported!"
    #endif
#endif

#ifdef COSEC_ENABLE_ASSERTS
    #define COSEC_ASSERT(x, ...) { if (!(x)) { LOG_CRIT("Assertion Failed: {0}:{1}: {2}", __FILE__, __LINE__, __VA_ARGS__); } }
    #define COSEC_CORE_ASSERT(x, ...) { if (!(x)) { LOG_CORE_CRIT("Assertion Failed: {0}:{1}: {2}", __FILE__, __LINE__, __VA_ARGS__); } }
#else
    #define COSEC_ASSERT(x, ...)
    #define COSEC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define DISPATCH_EVENT_FN(handler) [this](auto&& e) -> bool { return handler(std::forward<decltype(e)>(e)); }

// clang-format on
