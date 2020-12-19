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
        Shader* genShaderImpl(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) override;
        void deleteShaderImpl(const Shader& shader) const override;
        void useShaderImpl(const Shader& shader) const override;
        void resetShaderImpl() const override;

        // ArrayBuffer
        ArrayBuffer* genArrayBufferImpl(float* data, LzSizeT size) override;
        void bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const override;
        void setBufferLayoutImpl(const ArrayBuffer& buffer, const VertexBufferLayout& layout) const override;
        void resetArrayBufferImpl() const override;

        // IndexBuffer
        IndexBuffer* genIndexBufferImpl(uint32_t* indices, LzSizeT count) override;
        void bindIndexBufferImpl(const IndexBuffer& indexBuffer) const override;
        void resetIndexBufferImpl() const override;

        // VertexArray
        VertexArray* genVertexArrayImpl() override;
        void bindVertexArrayImpl(const VertexArray& vertexArray) const override;
        void unbindVertexArrayImpl(const VertexArray& vertexArray) const override;
        void resetVertexArrayImpl() const override;

        void initImpl() override;
        void terminateImpl() override;

    private:
        static uint32_t createShader(uint32_t type, const LzString& source);
        static uint32_t glTypeForPrimitiveType(const PrimitiveType& type);
    };
};