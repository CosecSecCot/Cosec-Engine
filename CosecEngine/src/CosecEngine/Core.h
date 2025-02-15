#pragma once

// clang-format off

#ifdef COSEC_WIN
    #ifdef COSEC_BUILD_DLL
        #define COSEC_API __declspec(dllexport)
    #else
        #define COSEC_API __declspec(dllimport)
    #endif
#elif COSEC_UNIX
    #ifdef COSEC_BUILD_DLL
        #define COSEC_API __attribute__((visibility("default")))
    #else
        #define COSEC_API
    #endif
#else
    #error "Platform not supported!"
#endif

#ifdef COSEC_ENABLE_ASSERTS
    #define COSEC_ASSERT(x, ...) { if (!(x)) { LOG_ERROR("Assertion Failed: {0}:{1}: {2}", __FILE__, __LINE__ __VA_ARGS__); } }
    #define COSEC_CORE_ASSERT(x, ...) { if (!(x)) { LOG_CORE_ERROR("Assertion Failed: {0}:{1}: {2}", __FILE__, __LINE__ __VA_ARGS__); } }
#else
    #define COSEC_ASSERT(x, ...)
    #define COSEC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

// clang-format on
