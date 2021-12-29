#ifdef __LZ_WIN

#include "DxGfx.hpp"
#include "DxShader.hpp"
#include "DxBuffer.hpp"
#include <lafez/misc/lafez_exception.hpp>
#include <lafez/utils/Log.hpp>
#include <lafez/core/assets/Asset.hpp>

namespace Lafez {
	DxGfx::DxGfx(
		HWND handleToWindow,
		ComPtr<ID3D11Device>* devicePtr,
		ComPtr<ID3D11DeviceContext>* deviceContextPtr
	) :
		Gfx(),
		swapChainPtr(nullptr),
		devicePtr(nullptr),
		deviceContextPtr(nullptr),
		renderTargetViewPtr(nullptr),
		modelCBufferPtr(nullptr),
		viewCBufferPtr(nullptr),
		projectionCBufferPtr(nullptr),
		rasterStatePtr(nullptr)
	{
		// swap chain and device creation
		DXGI_SWAP_CHAIN_DESC swapChainDesc{ };
		swapChainDesc.BufferDesc.Width = 0u;
		swapChainDesc.BufferDesc.Height = 0u;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0u;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1u;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2u;
		swapChainDesc.SampleDesc.Count = 1u;
		swapChainDesc.SampleDesc.Quality = 0u;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.Flags = 0u;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.OutputWindow = handleToWindow;

		UINT creationFlags = 0;

		#ifdef __LZ_DEBUG
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
			&(this->swapChainPtr),
			&(this->devicePtr),
			nullptr,
			&(this->deviceContextPtr)
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());

		// get the back buffer to create render target view, which is necessary for buffer clearing
		ID3D11Resource* backBufferPtr = nullptr;
		
		this->swapChainPtr->GetBuffer(
			0u,
			__uuidof(ID3D11Resource),
			reinterpret_cast<void**>(&backBufferPtr)
		);

		this->devicePtr->CreateRenderTargetView(
			backBufferPtr,
			nullptr,
			&renderTargetViewPtr
		);

		backBufferPtr->Release();

		this->deviceContextPtr->OMSetRenderTargets(
			1,
			renderTargetViewPtr.GetAddressOf(),
			nullptr
		);

		this->deviceContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// output the pointers for those needing (e.g ImGui)
		*devicePtr = this->devicePtr.Get();
		*deviceContextPtr = this->deviceContextPtr.Get();

		// create model buffers
		D3D11_BUFFER_DESC desc{ 0 };
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(glm::mat4);
		desc.MiscFlags = 0u;
		desc.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA resource{ 0 };
		glm::mat4 identity{ 1.0f };
		resource.pSysMem = &identity;
		resource.SysMemPitch = 0u;
		resource.SysMemSlicePitch = 0u;

		// model cbuffer
		result = this->devicePtr->CreateBuffer(
			&desc,
			&resource,
			&modelCBufferPtr
		);

		this->deviceContextPtr->VSSetConstantBuffers(
			MODEL_BUFFER_INDEX,
			1u,
			modelCBufferPtr.GetAddressOf()
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());

		// view cbuffer
		result = this->devicePtr->CreateBuffer(
			&desc,
			&resource,
			&viewCBufferPtr
		);

		this->deviceContextPtr->VSSetConstantBuffers(
			VIEW_BUFFER_INDEX,
			1u,
			viewCBufferPtr.GetAddressOf()
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());

		// projection cbuffer
		result = this->devicePtr->CreateBuffer(
			&desc,
			&resource,
			&projectionCBufferPtr
		);

		this->deviceContextPtr->VSSetConstantBuffers(
			PROJECTION_BUFFER_INDEX,
			1u,
			projectionCBufferPtr.GetAddressOf()
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());

		// set up rasterizer
		D3D11_RASTERIZER_DESC rasterDesc;
		ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.FrontCounterClockwise = TRUE;
		result = this->devicePtr->CreateRasterizerState(
			&rasterDesc,
			&rasterStatePtr
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());

		this->deviceContextPtr->RSSetState(rasterStatePtr.Get());

		LZ_ENGINE_INFO("[GFX] INITIALIZED TO D3D11");
	}

	DxGfx::~DxGfx() {
		LZ_ENGINE_INFO("[GFX] TERMINATED");
	}

	void DxGfx::clearBuffer(float r, float g, float b, float a) {
		const float color[4] = { r, g, b, a };
		deviceContextPtr->ClearRenderTargetView(renderTargetViewPtr.Get(), color);
	}

	void DxGfx::setViewport(float x, float y, float width, float height) {
		const D3D11_VIEWPORT viewport {
			x,
			y,
			width,
			height,
			.0f,
			1.0f
		};
		deviceContextPtr->RSSetViewports(1u, &viewport);
	}

	void DxGfx::swapBuffers() {
		auto result = swapChainPtr->Present(1u, 0u);
		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());
	}

	void DxGfx::drawList(unsigned int vertices) {
		deviceContextPtr->Draw(vertices, 0u);
	}

	void DxGfx::drawIndexed(unsigned int indices) {
		deviceContextPtr->DrawIndexed(indices, 0u, 0);
	}

	void DxGfx::setModel(const glm::mat4& model) {
		D3D11_MAPPED_SUBRESOURCE subResc;
		ZeroMemory(&subResc, sizeof(D3D11_MAPPED_SUBRESOURCE));

		deviceContextPtr->Map(
			modelCBufferPtr.Get(),
			0u,
			D3D11_MAP_WRITE_DISCARD,
			0u,
			&subResc
		);

		memcpy(subResc.pData, &model, sizeof(glm::mat4));
		deviceContextPtr->Unmap(modelCBufferPtr.Get(), 0u);
	}

	void DxGfx::setView(const glm::mat4& view) {
		D3D11_MAPPED_SUBRESOURCE subResc;
		ZeroMemory(&subResc, sizeof(D3D11_MAPPED_SUBRESOURCE));

		deviceContextPtr->Map(
			viewCBufferPtr.Get(),
			0u,
			D3D11_MAP_WRITE_DISCARD,
			0u,
			&subResc
		);

		memcpy(subResc.pData, &view, sizeof(glm::mat4));
		deviceContextPtr->Unmap(viewCBufferPtr.Get(), 0u);
	}

	void DxGfx::setProjection(const glm::mat4& projection) {
		D3D11_MAPPED_SUBRESOURCE subResc;
		ZeroMemory(&subResc, sizeof(D3D11_MAPPED_SUBRESOURCE));

		deviceContextPtr->Map(
			projectionCBufferPtr.Get(),
			0u,
			D3D11_MAP_WRITE_DISCARD,
			0u,
			&subResc
		);

		memcpy(subResc.pData, &projection, sizeof(glm::mat4));
		deviceContextPtr->Unmap(projectionCBufferPtr.Get(), 0u);
	}

	Bindable* DxGfx::genShader(
		const LzString& name,
		const LzString& vSource,
		const LzString& pSource,
		bool retain
	) {
		return new DxShader {
			devicePtr.Get(),
			deviceContextPtr.Get(),
			name,
			vSource,
			pSource
		};
	}

	Bindable* DxGfx::genVertexBuffer(
		float* data,
		LzSizeT dataSize,
		LzSizeT vertexCount
	) {
		return new DxVBuffer {
			devicePtr.Get(),
			deviceContextPtr.Get(),
			data,
			dataSize,
			vertexCount
		};
	}

	Bindable* DxGfx::genIndexBuffer(uint32_t* indices, LzSizeT indexCount) {
		return new DxIBuffer {
			devicePtr.Get(),
			deviceContextPtr.Get(),
			indices,
			indexCount
		};
	}

	Bindable* DxGfx::genVBLayout(
		VertexAttribute* attributes,
		LzSizeT attribCount,
		const Bindable* shader
	) {
		auto dxShader = dynamic_cast<const DxShader*>(shader);
		LZ_RUNTIME_GUARD((dxShader), "[DX GFX] Shader signature not found to create input layout");

		return new DxBufferLayout {
			devicePtr.Get(),
			deviceContextPtr.Get(),
			attributes,
			attribCount,
			dxShader->getVBlob()
		};
	}

	Bindable* DxGfx::genDefaultShader() {
		return genShader(
			"DEFAULT HLSL SHADER",
			Asset::getString("assets/shaders/hlsl/vertex_shader.hlsl"),
			Asset::getString("assets/shaders/hlsl/pixel_shader.hlsl"),
			false
		);
	}
};

#endif