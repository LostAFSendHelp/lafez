#pragma once
#include <lafez/lafez_pch.hpp>

namespace Lafez {
    struct WindowInfo {
        LzString mName;
        uint16_t mWidth;
        uint16_t mHeight;
        bool mShouldClose;

        WindowInfo(const char* name, uint16_t width, uint16_t height);
    };
};