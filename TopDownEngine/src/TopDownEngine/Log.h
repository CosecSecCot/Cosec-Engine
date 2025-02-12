#pragma once

#include "Core.h"

#include <memory>
#include <spdlog/spdlog.h>

namespace TopDown {

class TOPDOWN_API Log {
public:
    static void Init();

    static std::shared_ptr<spdlog::logger> getCoreLogger() { return s_CoreLogger; };
    static std::shared_ptr<spdlog::logger> getClientLogger() { return s_ClientLogger; };

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

} // namespace TopDown

// Core logging macros
#define LOG_CORE_TRACE(...) ::TopDown::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)  ::TopDown::Log::getCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)  ::TopDown::Log::getCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::TopDown::Log::getCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRIT(...)  ::TopDown::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client logging macros
#define LOG_TRACE(...) ::TopDown::Log::getClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)  ::TopDown::Log::getClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)  ::TopDown::Log::getClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::TopDown::Log::getClientLogger()->error(__VA_ARGS__)
#define LOG_CRIT(...)  ::TopDown::Log::getClientLogger()->critical(__VA_ARGS__)
