#include "log.hpp"

namespace Lafez {
    std::shared_ptr<spdlog::logger> Log::mEngineLog{ nullptr };
    std::shared_ptr<spdlog::logger> Log::mClientLog{ nullptr };

    Log::Log() {

    }

    Log::~Log() {

    }

    void Log::init() {
        mEngineLog = spdlog::stderr_color_mt("LAFEZ");
        mClientLog = spdlog::stderr_color_mt("CLIENT");
    }

    std::shared_ptr<spdlog::logger> Log::getEngineLog() {
        return mEngineLog;
    }

    std::shared_ptr<spdlog::logger> Log::getClientLog() {
        return mClientLog;
    }
}