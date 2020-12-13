#pragma once
#include <lafez/core/renderer/RendererBackend.hpp>

namespace Lafez {
    class GlRenderer : public RendererBackend {
    public:

        /**
         * @brief Construct a new OpenGL Renderer object
         */
        GlRenderer() = default;



        /**
         * @brief Destroy the Gl Renderer object
         */
        ~GlRenderer() = default;

    protected:

        // Shader
        virtual Shader* genShaderImpl(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) override;
        virtual void deleteShaderImpl(const Shader& shader) const override;
        virtual void useShaderImpl(const Shader& shader) const override;
        virtual void resetShaderImpl() const override;

        // ArrayBuffer
        virtual ArrayBuffer* genArrayBufferImpl(float* data, LzSizeT size) override;
        virtual void bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const override;
        virtual void resetArrayBufferImpl() const override;

        // IndexBuffer
        virtual IndexBuffer* genIndexBufferImpl(uint32_t* indices, LzSizeT count) override;
        virtual void bindIndexBufferImpl(const IndexBuffer& indexBuffer) const override;
        virtual void resetIndexBufferImpl() const override;

        virtual void initImpl() override;
        virtual void terminateImpl() override;

    private:
        uint32_t createShader(uint32_t type, const LzString& source) const;
    };
};