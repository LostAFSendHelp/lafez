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



        /**
         * @brief Write the specified string to the specified file. This function
         * overwrites all content of a file that already exists
         * 
         * @param path the path to the file to be written
         * @param content the text to be written to the file
         */
        static void writeString(const char* path, const char* content);
    };
};