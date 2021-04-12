#include "Log.hpp"

#ifdef __LZ_WIN
    #include <spdlog/sinks/msvc_sink.h>
#else
    #include <spdlog/sinks/stdout_color_sinks.h>
#endif

namespace Lafez {
    LzShrPtr<spdlog::logger> Log::mEngineLog{ nullptr };
    LzShrPtr<spdlog::logger> Log::mClientLog{ nullptr };

    Log::Log() {

    }

    Log::~Log() {

    }

    void Log::init() {
        if (mEngineLog != nullptr || mClientLog != nullptr) {
            spdlog::error("Logger(s) already initialized");
            return;
        }

        #ifdef __LZ_WIN
            auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        #else
            auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        #endif

        mEngineLog = std::make_shared<spdlog::logger>("LAFEZ", sink);
        mEngineLog->set_level(spdlog::level::trace);
        mClientLog = std::make_shared<spdlog::logger>("CLIENT", sink);
        mClientLog->set_level(spdlog::level::trace);

        mEngineLog->info("ENGINE LOG initialized");
        mClientLog->info("CLIENT LOG initialized");
    }

    LzShrPtr<spdlog::logger> Log::getEngineLog() {
        if (mEngineLog == nullptr) init();
        return mEngineLog;
    }

    LzShrPtr<spdlog::logger> Log::getClientLog() {
        if (mClientLog == nullptr) init();
        return mClientLog;
    }

    void Log::setEngineLogLevel(spdlog::level::level_enum level) {
        getEngineLog()->set_level(level);
    }

    void Log::setClientLogLevel(spdlog::level::level_enum level) {
        getClientLog()->set_level(level);
    }
}
