#pragma once
#include <lafezlib_export.h>
#include <lafez/lafez_pch.hpp>

namespace Lafez {
    class LAFEZLIB Shader {
    public:
        friend class RendererBackend;
        friend class GlRenderer;
        friend class DxRenderer;
        friend class VkRenderer;

        /// The renderer ID of the shader
        const uint32_t mID;
        /// The name of the shader
        const LzString mName;

        /**
         * @brief Destroy the Shader object
         */
        ~Shader() = default;



        /**
         * @brief Use the shader for subsequent object renderings, equivalent to calling RendererBackend::useShader(*this)
         */
        void use() const;

    private:

        /**
         * @brief Construct a new Shader object
         * 
         * @param id The renderer ID of the shader
         * @param name The name of the shader
         */
        Shader(uint32_t id, const LzString& name);
    };
};