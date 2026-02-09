#include <Log.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Engine{
    std::shared_ptr<spdlog::logger> Log::EngineLogger;
    std::shared_ptr<spdlog::logger> Log::ClientLogger;
    
    void Log::Init(){
        spdlog::set_pattern("%^[%T] %n: %v%$");

        EngineLogger = spdlog::stdout_color_mt("Engine");
        ClientLogger = spdlog::stderr_color_mt("Client");

        EngineLogger->set_level(spdlog::level::trace);
        ClientLogger->set_level(spdlog::level::trace);
        //set_level 筛选日志信息等级
    }

    std::shared_ptr<spdlog::logger>& Log::GetEngineLogger(){
        return EngineLogger;
    }

    std::shared_ptr<spdlog::logger>& Log::GetClientLogger(){
        return ClientLogger;
    }
}