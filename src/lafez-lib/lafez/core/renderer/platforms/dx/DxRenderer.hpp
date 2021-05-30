#pragma once
#ifdef __LZ_WIN

#include <lafez/core/renderer/RendererBackend.hpp>
#include <wrl.h>
#include <d3d11.h>
#include "DxShaderContainer.hpp"
#include "DxBuffer.hpp"

using Microsoft::WRL::ComPtr;

namespace Lafez {
    class DxRenderer : public RendererBackend {
    public:

        /**
         * @brief Construct a new D3D11 Renderer object
         */
        DxRenderer(HWND handleToWindow);



        /**
         * @brief Destroy the D3D11 Renderer object
         */
        ~DxRenderer() = default;

    protected:
        // Generic
        void clearBufferImpl(float red, float green, float blue, float alpha) override;
        void setViewportImpl(int x, int y, LzSizeT width, LzSizeT height) override;
        void swapBuffersImpl() override;

        // Shader
        Shader* genShaderImpl(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) override;
        void deleteShaderImpl(Shader* shader) override;
        void useShaderImpl(const Shader* shader) const override;
        void resetShaderImpl() const override;
        Shader* genDefaultShaderImpl() const override;

        // ArrayBuffer
        ArrayBuffer* genArrayBufferImpl(float* data, LzSizeT dataSize, LzSizeT vertexCount) override;
        void bindArrayBufferImpl(const ArrayBuffer* arrayBuffer) const override;
        void setBufferLayoutImpl(const ArrayBuffer* arrayBuffer, const VertexBufferLayout* layout, const Shader* shader) const override;
        void resetArrayBufferImpl() const override;

        // IndexBuffer
        IndexBuffer* genIndexBufferImpl(uint32_t * indices, LzSizeT indexCount) override;
        void bindIndexBufferImpl(const IndexBuffer* indexBuffer) const override;
        void resetIndexBufferImpl() const override;

        // VertexArray
        VertexArray* genVertexArrayImpl() override;
        void bindVertexArrayImpl(const VertexArray* vertexArray) const override;
        void unbindVertexArrayImpl(const VertexArray* vertexArray) const override;
        void resetVertexArrayImpl() const override;
        void drawVertexArrayImpl(const VertexArray* vertexArray) const override;

        void initImpl() override;
        void terminateImpl() override;

    private:
        ComPtr<IDXGISwapChain> mSwapChainPtr;
        ComPtr<ID3D11Device> mDevicePtr;
        ComPtr<ID3D11DeviceContext> mDeviceContextPtr;
        ComPtr<ID3D11RenderTargetView> mRenderTargetViewPtr;
        LzUnMap<uint32_t, DxShaderContainer> mShaderContainer;
        LzUnMap<uint32_t, DxBuffer> mBufferContainer;

        static DXGI_FORMAT getFormatForPrimitiveType(PrimitiveType type);
    };
};

#endif