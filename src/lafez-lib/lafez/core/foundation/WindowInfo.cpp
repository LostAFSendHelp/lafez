#include "WindowInfo.hpp"

namespace Lafez {
    WindowInfo::WindowInfo(const char* name, uint16_t width, uint16_t height) :
        mName(name),
        mWidth(width),
        mHeight(height),
        mShouldClose(false) {

    }
}