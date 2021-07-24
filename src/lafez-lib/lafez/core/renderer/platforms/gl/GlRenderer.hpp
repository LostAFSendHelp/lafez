#pragma once
#include <lafez/core/renderer/RendererBackend.hpp>

namespace Lafez {
    class GlRenderer : public RendererBackend {
    public:

        /**
         * @brief Construct a new OpenGL Renderer object
         */
        GlRenderer(GLFWwindow* windowPtr);



        /**
         * @brief Destroy the Gl Renderer object
         */
        ~GlRenderer() = default;

    protected:
        // Generic
        void clearBufferImpl(float red, float green, float blue, float alpha) override;
        void setViewportImpl(int x, int y, LzSizeT width, LzSizeT height) override;
        void swapBuffersImpl() override;

        // Shader
        Shader* genShaderImpl(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) override;
        void deleteShaderImpl(Shader& shader) override;
        void useShaderImpl(const Shader& shader) const override;
        void resetShaderImpl() const override;
        Shader* genDefaultShaderImpl() const override;

        // ArrayBuffer
        ArrayBuffer* genArrayBufferImpl(float* data, LzSizeT dataSize, LzSizeT vertexCount) override;
        bool bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const override;
        void setBufferLayoutImpl(ArrayBuffer& arrayBuffer, const VertexBufferLayout& layout, const Shader* shader) const override;
        void resetArrayBufferImpl() const override;

        // IndexBuffer
        IndexBuffer* genIndexBufferImpl(uint32_t* indices, LzSizeT indexCount) override;
        bool bindIndexBufferImpl(const IndexBuffer& indexBuffer) const override;
        void resetIndexBufferImpl() const override;

        // VertexArray
        VertexArray* genVertexArrayImpl() override;
        VertexArrayBindType bindVertexArrayImpl(const VertexArray& vertexArray) const override;
        void unbindVertexArrayImpl(const VertexArray& vertexArray) const override;
        void resetVertexArrayImpl() const override;
        void vertexArrayAddArrayBufferImpl(VertexArray& vertexArray, const LzShrPtr<ArrayBuffer>& arrayBuffer) const override;
        void drawVertexArrayImpl(const VertexArray& vertexArray) const override;

        void initImpl() override;
        void terminateImpl() override;

    private:
        static uint32_t createShader(uint32_t type, const LzString& source);
        static uint32_t glTypeForPrimitiveType(const PrimitiveType& type);

        GLFWwindow* mWindowPtr;
    };
};