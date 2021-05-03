#pragma once
#include <lafezlib_export.h>
#include <lafez/lafez_pch.hpp>

namespace Lafez {
    class LAFEZLIB Shader {
    public:

        /// The renderer ID of the shader
        const uint32_t mID;
        /// The name of the shader
        const LzString mName; 
        /// Whether the Shader object has been deleted. Do not set this value yourself, let the rendererbackend do the job
        bool mIsDeleted;



        /**
         * @brief Construct a new Shader object. Only for testing purposes should this constructor be called directly by client. For actual use, prefer RendererBackend::genShader(...) instead
         * 
         * @param id The renderer ID of the shader
         * @param name The name of the shader
         */
        Shader(uint32_t id, const LzString& name);



        /**
         * @brief Destroy the Shader object
         */
        ~Shader() = default;



        /**
         * @brief Use the shader for subsequent object renderings, equivalent to calling RendererBackend::useShader(this)
         */
        void use() const;

    private:
        
    };
};