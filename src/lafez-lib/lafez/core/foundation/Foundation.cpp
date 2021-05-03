#include <lafez/core/foundation/platforms/gl/GlWindow.hpp>
#include <lafez/core/foundation/platforms/dx/DxWindow.hpp>
#include <lafez/core/foundation/platforms/gl/GlImGui.hpp>
#include <lafez/core/foundation/platforms/gl/GlInput.hpp>
#include <lafez/core/foundation/Key.hpp>
#include <lafez/core/renderer/platforms/gl/GlRenderer.hpp>
#include <lafez/core/renderer/platforms/dx/DxRenderer.hpp>
#include "Foundation.hpp"

namespace Lafez {
    void startUp(FoundationPlatform platform) {
        Log::startUp();
        LZ_ENGINE_INFO("[----------LAFEZ STARTING UP----------]");
        LZ_ENGINE_GUARD_VOID((!Window::isInitialized() && !Input::isInitialized() && !ImGuiBackend::isInitialized()), "ATTEMPT TO RE-INITIALIZE FOUNDATION, ABORTING...");

        switch (platform) {
        case LZ_PLATFORM_GL: {
            Window::startUp<GlWindow>("Lafez GL", 1024, 768);
            auto window = static_cast<GLFWwindow*>(Window::getWindowPointer());
            RendererBackend::startUp<GlRenderer>(window);
            ImGuiBackend::startUp<GlImGui>(window);
            Input::startUp<GlInput>(window);

            break;
        }

        #ifdef __LZ_WIN
        case LZ_PLATFORM_DX: {
            Window::startUp<DxWindow>("Lafez DX", 1024, 768);
            auto window = static_cast<HWND>(Window::getWindowPointer());
            RendererBackend::startUp<DxRenderer>(window);

            break;
        }
        #endif


        case LZ_PLATFORM_VK:
            // TODO: setup for Vulkan
            break;

        default:
            return;
        }

        /* Key starts up with function param instead of template param
        * because it is a concrete type initialized with hard-set values
        * rather than abstract type functioning via polymorphism (this is
        * to avoid unnecessary vtable lookups)
        */
        Key::startUp(platform);
        RendererBackend::setViewport(0, 0, Window::getWidth(), Window::getHeight());
    }

    void shutDown() {
        LZ_ENGINE_INFO("[----------LAFEZ SHUTTING DOWN----------]");
        Input::shutDown();
        Key::shutDown();
        ImGuiBackend::shutDown();
        Window::shutDown();
        RendererBackend::shutDown();
        Log::shutDown();
    }
}