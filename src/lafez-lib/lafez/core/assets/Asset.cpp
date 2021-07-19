#include <filesystem>
#include <lafez/misc/BadFileException.hpp>
#include "Asset.hpp"

namespace Lafez {
    LzString Asset::getString(const char* path) {
        if (!std::filesystem::exists(path)) {
            LZ_THROW(BadFileException, path, "FILE NOT FOUND");
        } else {
            std::fstream f{ path };

            if (!f.good()) {
                LZ_THROW(BadFileException, path, "BAD FILE STATUS");
            }

            LzString buffer;
            LzString line;

            while (::std::getline(f, line)) {
                buffer += line;
                buffer.append("\n");
            }

            return buffer;
        }
    }

    void Asset::writeString(const char* path, const char* content) {
        std::fstream f{ path, std::ios::out | std::ios::trunc };
        f << content;
    }
}