#include "Asset.hpp"

namespace Lafez {
    LzString Asset::getString(const char* path) {
        ::std::fstream f{ path };
        LzString buffer;
        LzString line;

        while(::std::getline(f, line)) {
            buffer += line;
            buffer.append("\n");
        }

        return buffer;
    }
}