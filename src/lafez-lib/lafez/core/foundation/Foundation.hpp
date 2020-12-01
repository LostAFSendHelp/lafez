#pragma once
#include <lafez/core/foundation/platforms/gl/GlWindow.hpp>
#include <lafez/core/foundation/platforms/gl/GlImGui.hpp>
#include <lafez/core/foundation/platforms/gl/GlInput.hpp>

#define LZ_PLATFORM_NONE    ::Lafez::FoundationPlatform::None
#define LZ_PLATFORM_GL      ::Lafez::FoundationPlatform::GL
#define LZ_PLATFORM_DX      ::Lafez::FoundationPlatform::DX
#define LZ_PLATFORM_VK      ::Lafez::FoundationPlatform::VK

namespace Lafez {
    enum class FoundationPlatform: uint8_t {
        None = 0,
        GL,
        DX,
        VK
    };

    void LAFEZLIB startUp(FoundationPlatform platform);
    void LAFEZLIB shutDown();
};