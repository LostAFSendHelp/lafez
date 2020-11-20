#include "Log.hpp"

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

        mEngineLog = spdlog::stderr_color_mt("LAFEZ");
        mEngineLog->set_level(spdlog::level::trace);
        mClientLog = spdlog::stderr_color_mt("CLIENT");
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
