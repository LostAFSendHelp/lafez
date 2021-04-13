#pragma once
#include <lafezlib_export.h>
#include <lafez/lafez_pch.hpp>
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
        static void startUp();



        /**
         * @brief Shut the loggers down
         */
        static void shutDown();



        /**
         * @brief Get the Engine Log object used for logging messages within the engine
         * 
         * @return LzShrPtr<Log> 
         */
        static LzShrPtr<spdlog::logger> getEngineLog();



        /**
         * @brief Get the Client Log object used for logging messages arising on client side
         * 
         * @return LzShrPtr<Log> 
         */
        static LzShrPtr<spdlog::logger> getClientLog();



        /**
         * @brief Set log level for Engine Log
         * 
         * @param level The desired log level
         */
        static void setEngineLogLevel(spdlog::level::level_enum level);



        /**
         * @brief Set log level for Client Log
         * 
         * @param level The desired log level
         */
        static void setClientLogLevel(spdlog::level::level_enum level);



    private:
        /**
         * @brief Used for logging messages within the engine
         */
        static LzShrPtr<spdlog::logger> mEngineLog;



        /**
         * @brief Used for logging messages arising on client side
         */
        static LzShrPtr<spdlog::logger> mClientLog;
    };
};

#if defined __LZ_DBG || defined __LZ_RELDBG

    #define LZ_ENGINE_INFO(...) ::Lafez::Log::getEngineLog()->info(__VA_ARGS__)
    #define LZ_ENGINE_WARN(...) ::Lafez::Log::getEngineLog()->warn(__VA_ARGS__)
    #define LZ_ENGINE_ERR(...) ::Lafez::Log::getEngineLog()->error(__VA_ARGS__)

    #define LZ_CLIENT_INFO(...) ::Lafez::Log::getClientLog()->info(__VA_ARGS__)
    #define LZ_CLIENT_WARN(...) ::Lafez::Log::getClientLog()->warn(__VA_ARGS__)
    #define LZ_CLIENT_ERR(...) ::Lafez::Log::getClientLog()->error(__VA_ARGS__)

#else

    #define LZ_ENGINE_INFO(...)
    #define LZ_ENGINE_WARN(...)
    #define LZ_ENGINE_ERR(...)

    #define LZ_CLIENT_INFO(...)
    #define LZ_CLIENT_WARN(...)
    #define LZ_CLIENT_ERR(...)

#endif

#ifdef __LZ_WIN

    #define LZ_ENGINE_ASSERT(statement, message)\
        if (!statement) {\
            LZ_ENGINE_ERR("ASSERTION FAILED: {0}", message);\
            __debugbreak();\
        }

#else

    #define LZ_ENGINE_ASSERT(statement, message)

#endif

#define LZ_ENGINE_GUARD_VOID(statement, ...)\
    if (!statement) {\
        LZ_ENGINE_WARN(__VA_ARGS__);\
        return;\
    }

#define LZ_ENGINE_GUARD_VAL(statement, val, ...)\
    if (!statement) {\
        LZ_ENGINE_WARN(__VA_ARGS__);\
        return val;\
    }