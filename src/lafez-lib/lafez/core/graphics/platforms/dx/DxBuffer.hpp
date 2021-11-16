#pragma once
#ifdef __LZ_WIN

#include <lafez/core/graphics/Bindable.hpp>
#include <lafez/core/graphics/VertexAttribute.hpp>
#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

namespace Lafez {

	// vertex buffer
	class DxVBuffer final : public Bindable {
	public:
		const LzSizeT dataSize;
		const LzSizeT vertexCount;

		DxVBuffer(ID3D11Device* devicePtr, ID3D11DeviceContext* deviceContextPtr, float* data, LzSizeT dataSize, LzSizeT vertexCount);
		DxVBuffer(const DxVBuffer& other) = delete;
		DxVBuffer(DxVBuffer&& other) = delete;
		~DxVBuffer() = default;

		DxVBuffer& operator = (const DxVBuffer& other) = delete;
		DxVBuffer& operator = (DxVBuffer&& other) = delete;

		void bind() override;

	private:
		ID3D11Device* devicePtr;
		ID3D11DeviceContext* deviceContextPtr;
		ComPtr<ID3D11Buffer> bufferPtr;
	};



	// index buffer
	class DxIBuffer final : public Bindable {
	public:
		const LzSizeT indexCount;

		DxIBuffer(ID3D11Device* devicePtr, ID3D11DeviceContext* deviceContextPtr, uint32_t* indices, LzSizeT indexCount);
		DxIBuffer(const DxIBuffer& other) = delete;
		DxIBuffer(DxIBuffer&& other) = delete;
		~DxIBuffer() = default;

		DxIBuffer& operator = (const DxIBuffer& other) = delete;
		DxIBuffer& operator = (DxIBuffer&& other) = delete;

		void bind() override;

	private:
		ID3D11Device* devicePtr;
		ID3D11DeviceContext* deviceContextPtr;
		ComPtr<ID3D11Buffer> bufferPtr;
	};



	// buffer layout
	class DxBufferLayout final : public Bindable {
	public:
		DxBufferLayout(ID3D11Device* devicePtr, ID3D11DeviceContext* deviceContextPtr, VertexAttribute* attributes, LzSizeT attribCount, ID3DBlob* vBlob);
		DxBufferLayout(const DxBufferLayout& other) = delete;
		DxBufferLayout(DxBufferLayout&& other) = delete;
		~DxBufferLayout() = default;

		DxBufferLayout& operator = (const DxBufferLayout& other) = delete;
		DxBufferLayout& operator = (DxBufferLayout&& other) = delete;

		void bind() override;

	private:
		ID3D11Device* devicePtr;
		ID3D11DeviceContext* deviceContextPtr;
		ComPtr<ID3D11InputLayout> inputLayoutPtr;

		static DXGI_FORMAT getFormatForPrimitiveType(PrimitiveType type);
	};
};

#endif