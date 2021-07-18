#ifdef __LZ_WIN

#include "DxRenderer.hpp"
#include <lafez/utils/Log.hpp>
#include <lafez/misc/lafez_exception.hpp>
#include <lafez/core/assets/Asset.hpp>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using Microsoft::WRL::ComPtr;

namespace Lafez {
    DxRenderer::DxRenderer(
        HWND handleToWindow,
        ComPtr<ID3D11Device>* devicePtr,
        ComPtr<ID3D11DeviceContext>* deviceContextPtr
    ) :
        mSwapChainPtr(nullptr),
        mDevicePtr(nullptr),
        mDeviceContextPtr(nullptr),
        mRenderTargetViewPtr(nullptr),
        mShaderContainer()
    {

        DXGI_SWAP_CHAIN_DESC swapChainDesc{ };
        swapChainDesc.BufferDesc.Width = 0u;
        swapChainDesc.BufferDesc.Height = 0u;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 1;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Windowed = TRUE;
        swapChainDesc.Flags = 0;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDesc.OutputWindow = handleToWindow;

        UINT creationFlags = 0;
        
        #ifdef __LZ_DBG
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        #endif 

        auto result = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &mSwapChainPtr,
            &mDevicePtr,
            nullptr,
            &mDeviceContextPtr
        );

        if (result != S_OK) {
            throw LZ_WINEXCEPT(result);
        }

        ID3D11Resource* backBufferPtr = nullptr;
        mSwapChainPtr->GetBuffer(0u, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBufferPtr));
        mDevicePtr->CreateRenderTargetView(
            backBufferPtr,
            nullptr,
            &mRenderTargetViewPtr
        );

        backBufferPtr->Release();

        mDeviceContextPtr->OMSetRenderTargets(1, mRenderTargetViewPtr.GetAddressOf(), nullptr);
        mDeviceContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        *devicePtr = mDevicePtr.Get();
        *deviceContextPtr = mDeviceContextPtr.Get();
    }

    /********************************************************
    *                      Singleton                        *
    ********************************************************/

    void DxRenderer::initImpl() {
        LZ_ENGINE_INFO("DX WINDOW INITIALIZED");
        LZ_ENGINE_INFO("RENDERER INITIALIZED TO DIRECTX");
    }

    void DxRenderer::terminateImpl() {
        LZ_ENGINE_INFO("DIRECTX RENDERER TERMINATED");
    }



    /********************************************************
    *                        Shader                         *
    ********************************************************/

    void DxRenderer::clearBufferImpl(float red, float green, float blue, float alpha) {
        const float color[] = { red, green, blue, alpha };
        mDeviceContextPtr->ClearRenderTargetView(mRenderTargetViewPtr.Get(), color);
    }

    void DxRenderer::setViewportImpl(int x, int y, LzSizeT width, LzSizeT height) {
        D3D11_VIEWPORT viewport{
            (FLOAT)x,
            (FLOAT)y,
            (FLOAT)width,
            (FLOAT)height,
            .0f,
            1.0f
        };

        mDeviceContextPtr->RSSetViewports(1, &viewport);
    }

    void DxRenderer::swapBuffersImpl() {
        mSwapChainPtr->Present(1u, 0u);
    }



    /********************************************************
    *                        Shader                         *
    ********************************************************/

    Shader* DxRenderer::genShaderImpl(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain) {
        auto flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef __LZ_DBG
        flags |= D3DCOMPILE_DEBUG;
#endif

        ComPtr<ID3DBlob> vBlobPtr = nullptr, pBlobPtr = nullptr, errorBlobPtr = nullptr;

        // compile vertex shader
        LZ_ENGINE_ASSERT(
            SUCCEEDED(
                D3DCompile(
                    vSource.c_str(),
                    vSource.size(),
                    nullptr,
                    nullptr,
                    nullptr,
                    "vs_main",
                    "vs_5_0",
                    flags,
                    0,
                    &vBlobPtr,
                    &errorBlobPtr
                )
            ),
            (char*)errorBlobPtr->GetBufferPointer()
        );

        // compile pixel shader
        LZ_ENGINE_ASSERT(
            SUCCEEDED(
                D3DCompile(
                    fSource.c_str(),
                    fSource.size(),
                    nullptr,
                    nullptr,
                    nullptr,
                    "ps_main",
                    "ps_5_0",
                    flags,
                    0,
                    &pBlobPtr,
                    &errorBlobPtr
                )
            ),
            (char*)errorBlobPtr->GetBufferPointer()
        );

        // container pointers for shaders
        ComPtr<ID3D11VertexShader> vShaderPtr = nullptr;
        ComPtr<ID3D11PixelShader> pShaderPtr = nullptr;

        // create vertex shader
        LZ_ENGINE_ASSERT(
            SUCCEEDED(
                mDevicePtr->CreateVertexShader(
                    vBlobPtr->GetBufferPointer(),
                    vBlobPtr->GetBufferSize(),
                    nullptr,
                    &vShaderPtr
                )
            ),
            "Failure creating vertex shader"
        );

        // create pixel shader
        LZ_ENGINE_ASSERT(
            SUCCEEDED(
                mDevicePtr->CreatePixelShader(
                    pBlobPtr->GetBufferPointer(),
                    pBlobPtr->GetBufferSize(),
                    nullptr,
                    &pShaderPtr
                )
            ),
            "Failure creating pixel shader"
        );

        // store D3D11 shaders in private container, only expose via IDs
        auto id = DxShaderContainer::getCount();
        mShaderContainer.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(id),
            std::forward_as_tuple(vShaderPtr, pShaderPtr, vBlobPtr)
        );

        LZ_ENGINE_INFO("Dx Shader generated with ID: {0} | Current shader counts: {1}", id, DxShaderContainer::getCount());
        return new Shader{ id, name };
    }

    void DxRenderer::deleteShaderImpl(Shader* shader) {
        LZ_ENGINE_GUARD_VOID(shader, "Nullptr passed as shader");
        mShaderContainer.erase(shader->mID);
    }

    void DxRenderer::useShaderImpl(const Shader* shader) const {
        LZ_ENGINE_GUARD_VOID(shader, "Nullptr passed as shader");
        mDeviceContextPtr->VSSetShader(mShaderContainer.at(shader->mID).getVertexShaderPtr().Get(), nullptr, 0);
        mDeviceContextPtr->PSSetShader(mShaderContainer.at(shader->mID).getPixelShaderPtr().Get(), nullptr, 0);
    }

    void DxRenderer::resetShaderImpl() const {
        mDeviceContextPtr->VSSetShader(nullptr, nullptr, 0);
        mDeviceContextPtr->PSSetShader(nullptr, nullptr, 0);
    }

    Shader* DxRenderer::genDefaultShaderImpl() const {
        return genShader(
            "DEFAULT HLSL SHADER",
            Asset::getString("assets/shaders/hlsl/vertex_shader.hlsl"),
            Asset::getString("assets/shaders/hlsl/pixel_shader.hlsl"),
            false
        );
    }



    /********************************************************
    *                      ArrayBuffer                      *
    ********************************************************/

    ArrayBuffer* DxRenderer::genArrayBufferImpl(float* data, LzSizeT dataSize, LzSizeT vertexCount) {
        D3D11_BUFFER_DESC bufferDesc{ 0 };
        bufferDesc.ByteWidth = dataSize;
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0u;
        bufferDesc.MiscFlags = 0u;
        bufferDesc.StructureByteStride = dataSize / vertexCount;

        D3D11_SUBRESOURCE_DATA subRescData{ 0 };
        subRescData.pSysMem = data;

        ComPtr<ID3D11Buffer> bufferPtr{ nullptr };

        LZ_ENGINE_ASSERT(
            SUCCEEDED(
                mDevicePtr->CreateBuffer(
                    &bufferDesc,
                    &subRescData,
                    &bufferPtr
                )
            ),
            "Failed to create Buffer"
        );

        auto id = DxBuffer::getCount();
        mBufferContainer.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(id),
            std::forward_as_tuple(bufferPtr)
        );

        return new ArrayBuffer{ id, dataSize, vertexCount };
    }

    void DxRenderer::bindArrayBufferImpl(const ArrayBuffer* arrayBuffer) const {
        LZ_ENGINE_GUARD_VOID(arrayBuffer, "Nullptr passed as array buffer");
        auto bufferPtr = mBufferContainer.at(arrayBuffer->mID).getBufferPtr();
        UINT stride = arrayBuffer->mDataSize / arrayBuffer->mVertexCount;
        UINT offset = 0;

        mDeviceContextPtr->IASetVertexBuffers(
            0,
            1,
            bufferPtr.GetAddressOf(),
            &stride,
            &offset
        );
    }

    void DxRenderer::setBufferLayoutImpl(const ArrayBuffer* arrayBuffer, const VertexBufferLayout* layout, const Shader* shader) const {
        LZ_ENGINE_GUARD_VOID(layout, "Nullptr passed as vertex buffer layout");
        const auto elementCount = layout->getAttributes().size();
        D3D11_INPUT_ELEMENT_DESC desc[elementCount];

        ComPtr<ID3D11InputLayout> inputLayoutPtr{ nullptr };

        int index = 0;
        for (const auto& attrib : layout->getAttributes()) {
            D3D11_INPUT_ELEMENT_DESC inputDesc{ 0 };

            inputDesc.SemanticName = attrib.getName().c_str();
            inputDesc.SemanticIndex = 0;
            inputDesc.Format = getFormatForPrimitiveType(attrib.mType);
            inputDesc.InputSlot = 0;
            inputDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
            inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            inputDesc.InstanceDataStepRate = 0;

            desc[index++] = inputDesc;
        }

        auto blobPtr = mShaderContainer.at(shader->mID).getShaderBlobPtr();

        LZ_ENGINE_ASSERT(
            SUCCEEDED(
                mDevicePtr->CreateInputLayout(
                    desc,
                    elementCount,
                    blobPtr->GetBufferPointer(),
                    blobPtr->GetBufferSize(),
                    &inputLayoutPtr
                )
            ),
            "Failed to create input layout"
        );

        mDeviceContextPtr->IASetInputLayout(inputLayoutPtr.Get());
    }

    void DxRenderer::resetArrayBufferImpl() const {
        mDeviceContextPtr->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
    }



    /********************************************************
    *                      ArrayBuffer                      *
    ********************************************************/

    IndexBuffer* DxRenderer::genIndexBufferImpl(uint32_t* indices, LzSizeT count) {
        return nullptr;
    }

    void DxRenderer::bindIndexBufferImpl(const IndexBuffer* indexBuffer) const {

    }

    void DxRenderer::resetIndexBufferImpl() const {

    }



    /********************************************************
    *                      VertexArray                      *
    ********************************************************/

    VertexArray* DxRenderer::genVertexArrayImpl() {
        static uint32_t vaCount = 0;
        return new VertexArray{ vaCount++ };
    }

    void DxRenderer::bindVertexArrayImpl(const VertexArray* vertexArray) const {
        LZ_ENGINE_GUARD_VOID(vertexArray, "Nullptr passed as vertex array");
        bindArrayBufferImpl(vertexArray->getArrayBuffer().get());
    }

    void DxRenderer::unbindVertexArrayImpl(const VertexArray* vertexArray) const {
        LZ_ENGINE_GUARD_VOID(vertexArray, "Nullptr passed as vertex array");
    }

    void DxRenderer::resetVertexArrayImpl() const {
        resetArrayBufferImpl();
    }

    void DxRenderer::vertexArrayAddArrayBufferImpl(VertexArray* vertexArray, const ArrayBuffer* arrayBuffer) const {

    }

    void DxRenderer::drawVertexArrayImpl(const VertexArray* vertexArray) const {
        LZ_ENGINE_GUARD_VOID(vertexArray, "Nullptr passed as vertex array");
        bindVertexArrayImpl(vertexArray);
        mDeviceContextPtr->Draw(vertexArray->getArrayBuffer()->mVertexCount, 0);
    }



    /********************************************************
    *                     private funcs                     *
    ********************************************************/

    DXGI_FORMAT DxRenderer::getFormatForPrimitiveType(PrimitiveType type) {
        switch (type)
        {
        case LZ_PTYPE_VEC3I:
            return DXGI_FORMAT_R32G32B32_SINT;
        case LZ_PTYPE_VEC4I:
            return DXGI_FORMAT_R32G32B32A32_SINT;
        case LZ_PTYPE_VEC3F:
            return DXGI_FORMAT_R32G32B32_FLOAT;
        case LZ_PTYPE_VEC4F:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;
        default:
            return DXGI_FORMAT_UNKNOWN;
        }
    }
}

#endif