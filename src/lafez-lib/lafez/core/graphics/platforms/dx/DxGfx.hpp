#pragma once
#ifdef __LZ_WIN

#include <lafez/core/graphics/Gfx.hpp>
#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

namespace Lafez {
	class DxGfx final : public Gfx {
	public:
		DxGfx(HWND handleToWindow, ComPtr<ID3D11Device>* devicePtr, ComPtr<ID3D11DeviceContext>* deviceContextPtr);
		~DxGfx();

		DxGfx(const DxGfx& other) = delete;
		DxGfx(DxGfx&& other) = delete;
		DxGfx& operator=(const DxGfx& other) = delete;
		DxGfx& operator=(DxGfx&& other) = delete;

		void clearBuffer(float r, float g, float b, float a) override;
		void setViewport(float x, float y, float width, float height) override;
		void swapBuffers() override;
		void drawList(unsigned int vertices) override;
		void drawIndexed(unsigned int indices) override;
		void setModel(const glm::mat4& model) override;
		void setView(const glm::mat4& view) override;
		void setProjection(const glm::mat4& perspective) override;
		Bindable* genShader(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) override;
		Bindable* genVertexBuffer(float* data, LzSizeT dataSize, LzSizeT vertexCount) override;
		Bindable* genIndexBuffer(uint32_t* indices, LzSizeT indexCount) override;
		Bindable* genVBLayout(VertexAttribute* attributes, LzSizeT attribCount, const Bindable* shader) override;
		Bindable* genDefaultShader() override;

	private:
		ComPtr<IDXGISwapChain> swapChainPtr;
		ComPtr<ID3D11Device> devicePtr;
		ComPtr<ID3D11DeviceContext> deviceContextPtr;
		ComPtr<ID3D11RenderTargetView> renderTargetViewPtr;
		ComPtr<ID3D11RasterizerState> rasterStatePtr;

		ComPtr<ID3D11Buffer> modelCBufferPtr;
		ComPtr<ID3D11Buffer> viewCBufferPtr;
		ComPtr<ID3D11Buffer> projectionCBufferPtr;
	};
};

#endif