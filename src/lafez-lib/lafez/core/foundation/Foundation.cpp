#include <lafez/core/foundation/platforms/gl/GlWindow.hpp>
#include <lafez/core/foundation/platforms/gl/GlImGui.hpp>
#include <lafez/core/foundation/platforms/gl/GlInput.hpp>
#include <lafez/core/renderer/platforms/GlRenderer.hpp>
#include "Foundation.hpp"

namespace Lafez {
    void startUp(FoundationPlatform platform) {
        LZ_ENGINE_GUARD_VOID((!Window::isInitialized() && !Input::isInitialized() && !ImGuiBackend::isInitialized()), "ATTEMPT TO RE-INITIALIZE FOUNDATION, ABORTING...");

        switch (platform) {
        case LZ_PLATFORM_GL: {
            RendererBackend::startUp<GlRenderer>();
            Window::startUp<GlWindow>("Lafez GL", 1024, 768);
            auto window = static_cast<GLFWwindow*>(Window::getWindowPointer());
            ImGuiBackend::startUp<GlImGui>(window);
            Input::startUp<GlInput>(window);

            break;
        }

        case LZ_PLATFORM_DX:
            // TODO: setup for Direct3D
            break;

        case LZ_PLATFORM_VK:
            // TODO: setup for Vulkan
            break;

        default:
            return;
        }
    }

    void shutDown() {
        Input::shutDown();
        ImGuiBackend::shutDown();
        Window::shutDown();
        RendererBackend::shutDown();
    }
}