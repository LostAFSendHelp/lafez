#pragma once
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>

#define LZ_GAPI_NONE    ::Lafez::GraphicsAPI::None
#define LZ_GAPI_GL      ::Lafez::GraphicsAPI::GL
#define LZ_GAPI_VK      ::Lafez::GraphicsAPI::VK

#ifdef __LZ_WIN
#define LZ_GAPI_DX  ::Lafez::GraphicsAPI::DX
#endif

namespace Lafez {
    enum class GraphicsAPI: uint8_t {
        /// Dummy case, should not be called
        None = 0,
        /// OpenGL3. Note: Window managed with GLFW internally 
        GL,
        /// Vulkan - Unimplemented 
        VK,

        #ifdef __LZ_WIN
        /// D3D11. Note: Window managed with winAPI internally 
        DX,
        #endif
    };

    /// <summary>
    /// Configs with which to initialize the engine
    /// </summary>
    struct LAFEZLIB EngineConfigs {
    public:
        /// The graphics API to initialize the engine with
        const GraphicsAPI mGAPI;

        EngineConfigs(GraphicsAPI gapi) noexcept;
        EngineConfigs(EngineConfigs&& other) = default;
        EngineConfigs(const EngineConfigs& other) = default;
        ~EngineConfigs() = default;

        EngineConfigs& operator=(const EngineConfigs& other) = delete;
        EngineConfigs& operator=(EngineConfigs&& other) = delete;

        LzString toJson() const;

        static EngineConfigs fromJson(const char* path);
        static EngineConfigs fromJsonString(const LzString& json);
        static EngineConfigs createDefault() noexcept;
        static EngineConfigs loadDefault() noexcept;

    private:
    };

    void LAFEZLIB startUp(const EngineConfigs& engineConfigs);
    void LAFEZLIB shutDown();
};