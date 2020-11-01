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