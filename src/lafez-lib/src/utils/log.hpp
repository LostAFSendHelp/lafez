#pragma once
#include <lafezlib_export.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Lafez {
    class LAFEZLIB Log final {
    public:

        Log();
        ~Log();



        /**
         * @brief Initialize engine logger and client logger
         */
        static void init();



        /**
         * @brief Get the Engine Log object used for logging messages within the engine
         * 
         * @return std::shared_ptr<Log> 
         */
        static std::shared_ptr<spdlog::logger> getEngineLog();



        /**
         * @brief Get the Client Log object used for logging messages arising on client side
         * 
         * @return std::shared_ptr<Log> 
         */
        static std::shared_ptr<spdlog::logger> getClientLog();



    private:
        /**
         * @brief Used for logging messages within the engine
         */
        static std::shared_ptr<spdlog::logger> mEngineLog;



        /**
         * @brief Used for logging messages arising on client side
         */
        static std::shared_ptr<spdlog::logger> mClientLog;
    };
};

#ifdef _DEBUG

    #define LZ_ENGINE_INFO(...) Lafez::Log::getEngineLog()->info(__VA_ARGS__)
    #define LZ_ENGINE_WARN(...) Lafez::Log::getEngineLog()->warn(__VA_ARGS__)
    #define LZ_ENGINE_ERR(...) Lafez::Log::getEngineLog()->error(__VA_ARGS__)

    #define LZ_CLIENT_INFO(...) Lafez::Log::getClientLog()->info(__VA_ARGS__)
    #define LZ_CLIENT_WARN(...) Lafez::Log::getClientLog()->warn(__VA_ARGS__)
    #define LZ_CLIENT_ERR(...) Lafez::Log::getClientLog()->error(__VA_ARGS__)

#else

    #define LZ_ENGINE_INFO(...)
    #define LZ_ENGINE_WARN(...)
    #define LZ_ENGINE_ERR(...)

    #define LZ_CLIENT_INFO(...)
    #define LZ_CLIENT_WARN(...)
    #define LZ_CLIENT_ERR(...)

#endif