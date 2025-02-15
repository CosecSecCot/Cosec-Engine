#pragma once

#include "Core.h"

#include <pch.h>
#include <spdlog/spdlog.h>

namespace Cosec {

class COSEC_API Log {
public:
    static void Init();

    static std::shared_ptr<spdlog::logger> getCoreLogger() { return s_CoreLogger; };
    static std::shared_ptr<spdlog::logger> getClientLogger() { return s_ClientLogger; };

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

} // namespace Cosec

// Core logging macros
#define LOG_CORE_TRACE(...) ::Cosec::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)  ::Cosec::Log::getCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)  ::Cosec::Log::getCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::Cosec::Log::getCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRIT(...)  ::Cosec::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client logging macros
#define LOG_TRACE(...) ::Cosec::Log::getClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)  ::Cosec::Log::getClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)  ::Cosec::Log::getClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Cosec::Log::getClientLogger()->error(__VA_ARGS__)
#define LOG_CRIT(...)  ::Cosec::Log::getClientLogger()->critical(__VA_ARGS__)
