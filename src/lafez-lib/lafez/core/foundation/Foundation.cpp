#include <lafez/core/foundation/platforms/gl/GlWindow.hpp>
#include <lafez/core/foundation/platforms/dx/DxWindow.hpp>
#include <lafez/core/foundation/platforms/gl/GlImGui.hpp>
#include <lafez/core/foundation/platforms/gl/GlInput.hpp>
#include <lafez/core/foundation/Key.hpp>
#include <lafez/core/graphics/platforms/gl/GlGfx.hpp>
#include <lafez/core/graphics/platforms/dx/DxGfx.hpp>
#include <lafez/core/foundation/platforms/dx/DxImGui.hpp>
#include <lafez/core/assets/Asset.hpp>
#include <nlohmann/json.hpp>
#include <lafez/misc/BadFileException.hpp>
#include "Foundation.hpp"

using Json = nlohmann::json;

namespace Lafez {
    void startUp(const EngineConfigs& engineConfigs) {
        Log::startUp();
        LZ_ENGINE_INFO("[----------LAFEZ STARTING UP----------]");
        LZ_ENGINE_GUARD_VOID((!Window::isInitialized() && !Input::isInitialized() && !ImGuiBackend::isInitialized()), "ATTEMPT TO RE-INITIALIZE FOUNDATION, ABORTING...");

        switch (engineConfigs.mGAPI) {
        case LZ_GAPI_GL: {
            Window::startUp<GlWindow>("Lafez GL", 1280, 768);
            auto window = static_cast<GLFWwindow*>(Window::getWindowPointer());
            Gfx::startUp<GlGfx>(window);
            ImGuiBackend::startUp<GlImGui>(window);
            Input::startUp<GlInput>(window);

            break;
        }

        #ifdef __LZ_WIN
        case LZ_GAPI_DX: {
            Window::startUp<DxWindow>("Lafez DX", 1280, 768, &ImGui_ImplWin32_WndProcHandler);
            auto window = static_cast<HWND>(Window::getWindowPointer());

            ComPtr<ID3D11Device> devicePtr{ nullptr };
            ComPtr<ID3D11DeviceContext> deviceContextPtr{ nullptr };
            Gfx::startUp<DxGfx>(window, &devicePtr, &deviceContextPtr);
            ImGuiBackend::startUp<DxImGui>(window, devicePtr, deviceContextPtr);

            break;
        }
        #endif


        case LZ_GAPI_VK:
            // TODO: setup for Vulkan
            break;

        default:
            return;
        }

        /**
         * Key starts up with function param instead of template param
         * because it is a concrete type initialized with hard-set values
         * rather than abstract type functioning via polymorphism (this is
         * to avoid unnecessary vtable lookups)
         */
        Key::startUp(engineConfigs.mGAPI);
        Gfx::gfx()->setViewport(0, 0, Window::getWidth(), Window::getHeight());
    }

    void shutDown() {
        LZ_ENGINE_INFO("[----------LAFEZ SHUTTING DOWN----------]");
        Input::shutDown();
        Key::shutDown();
        ImGuiBackend::shutDown();
        Window::shutDown();
        Gfx::shutDown();
        Log::shutDown();
    }

    EngineConfigs::EngineConfigs(GraphicsAPI gapi) noexcept : mGAPI(gapi) {

    }

    LzString EngineConfigs::toJson() const {
        LzString apiString = "GL";
        
        switch (mGAPI) {
        
        case LZ_GAPI_DX: {
            apiString = "DX";
            break;
        }
        
        case LZ_GAPI_VK: {
            apiString = "VK";
            break;
        }

        default:
            break;
        }

        Json config;
        config["graphics_api"] = apiString;
        return config.dump(4);
    }

    EngineConfigs EngineConfigs::fromJson(const char* path) {
        const auto rawData = Asset::getString(path);
        return fromJsonString(rawData);
    }

    EngineConfigs EngineConfigs::fromJsonString(const LzString& jsonString) {
        const auto parsedData = Json::parse(jsonString);
        const auto val = parsedData.value<LzString>("graphics_api", "GL");

        auto gapi = LZ_GAPI_GL;

        if (val == "DX") {
        #ifdef __LZ_WIN
            gapi = LZ_GAPI_DX;
        #else
            LZ_ENGINE_WARN("ABORTING ATTEMPT TO INITIALIZE GRAPHICS API TO DX, DEFAULTING TO GL INSTEAD...");
        #endif // __LZ_WIN
        }
        else if (val == "VK") {
            LZ_ENGINE_WARN("LAFEZ CURRENTLY DOES NOT SUPPORT VK, DEFAULTING TO GL INSTEAD...");
        }

        return { gapi };
    }

    EngineConfigs EngineConfigs::createDefault() noexcept {
        return { LZ_GAPI_GL };
    }

    EngineConfigs EngineConfigs::loadDefault() noexcept {
        try {
            return fromJson("engine_configs.json");
        } catch (const std::exception& exception) {
            LZ_ENGINE_WARN("ERROR READING CONFIG DATA, CREATING DEFAULT DATA INSTEAD...\n{0}", exception.what());
            auto configs = createDefault();
            
            try {
                Asset::writeString("engine_configs.json", configs.toJson().c_str());
            } catch (const std::exception& exception) {
                LZ_ENGINE_WARN("ERROR WRITING CONFIG DATA, CHANGES WILL NOT BE SAVED\nINFO: {0}", exception.what());
            }
            
            return configs;
        }
    }
}