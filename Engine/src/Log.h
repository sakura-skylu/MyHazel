#pragma once
#include <memory>
#include <spdlog/spdlog.h>

namespace Engine{
class Log{
    public:
    static std::shared_ptr<spdlog::logger>& GetEngineLogger();
    static std::shared_ptr<spdlog::logger>& GetClientLogger();
    static void Init();

    private:
    static std::shared_ptr<spdlog::logger> EngineLogger;
    static std::shared_ptr<spdlog::logger> ClientLogger;
};

}

#define ENGINE_INFO(...)  ::Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define ENGINE_ERROR(...) ::Engine::Log::GetEngineLogger()->error(__VA_ARGS__)

#define APP_INFO(...)     ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define APP_ERROR(...)    ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)

