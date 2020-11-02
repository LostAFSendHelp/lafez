#include "log.hpp"

namespace Lafez {
    std::shared_ptr<spdlog::logger> Log::mEngineLog{ nullptr };
    std::shared_ptr<spdlog::logger> Log::mClientLog{ nullptr };

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

    std::shared_ptr<spdlog::logger> Log::getEngineLog() {
        if (mEngineLog == nullptr) init();
        return mEngineLog;
    }

    std::shared_ptr<spdlog::logger> Log::getClientLog() {
        if (mClientLog == nullptr) init();
        return mClientLog;
    }
}
