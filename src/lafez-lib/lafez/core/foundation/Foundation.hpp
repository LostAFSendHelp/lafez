#pragma once
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>

#define LZ_PLATFORM_NONE    ::Lafez::FoundationPlatform::None
#define LZ_PLATFORM_GL      ::Lafez::FoundationPlatform::GL
#define LZ_PLATFORM_VK      ::Lafez::FoundationPlatform::VK

#ifdef __LZ_WIN
    #define LZ_PLATFORM_DX  ::Lafez::FoundationPlatform::DX
#endif

namespace Lafez {
    enum class FoundationPlatform: uint8_t {
        None = 0,
        GL,
        VK,

        #ifdef __LZ_WIN
            DX,
        #endif
    };

    void LAFEZLIB startUp(FoundationPlatform platform);
    void LAFEZLIB shutDown();
};