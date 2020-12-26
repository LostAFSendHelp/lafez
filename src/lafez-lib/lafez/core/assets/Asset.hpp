#pragma once
#include <lafez/lafez_pch.hpp>
#include <exports/lafezlib_export.h>

namespace Lafez {
    class LAFEZLIB Asset final {
    public:
        Asset() = default;
        ~Asset() = default;

        /**
         * @brief Read all texts in the file at the specified path into a string
         * 
         * @param path The path to the file containing the texts to retrieve
         * @return LzString 
         */
        static LzString getString(const char* path);
    };
};