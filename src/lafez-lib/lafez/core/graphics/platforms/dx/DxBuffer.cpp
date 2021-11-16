#ifdef __LZ_WIN

#include "DxBuffer.hpp"
#include <lafez/misc/lafez_exception.hpp>
#pragma comment(lib, "d3d11.lib")

namespace Lafez {

	// DxVBuffer
	DxVBuffer::DxVBuffer(
		ID3D11Device* devicePtr,
		ID3D11DeviceContext* deviceContextPtr,
		float* data,
		LzSizeT dataSize,
		LzSizeT vertexCount
	) : 
		Bindable(LZ_BIND_TYPE_VBUFF, vertexCount),
		devicePtr(devicePtr),
		deviceContextPtr(deviceContextPtr),
		vertexCount(vertexCount),
		dataSize(dataSize),
		bufferPtr(nullptr)
	{
		LZ_RUNTIME_GUARD((devicePtr && deviceContextPtr), "[DxBuffer] Device and device context must not be NULL");
		D3D11_BUFFER_DESC desc { 0 };
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = dataSize;
		desc.CPUAccessFlags = 0u;
		desc.MiscFlags = 0u;
		desc.StructureByteStride = dataSize / vertexCount;

		D3D11_SUBRESOURCE_DATA subresc { 0 };
		subresc.pSysMem = data;
		
		auto result = devicePtr->CreateBuffer(
			&desc,
			&subresc,
			&bufferPtr
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());
	}

	void DxVBuffer::bind() {
		LZ_RUNTIME_GUARD((devicePtr && deviceContextPtr), "[DxBuffer] Device and device context must not be NULL");
		UINT stride = dataSize / vertexCount;
		UINT offset = 0u;
		
		deviceContextPtr->IASetVertexBuffers(
			0u,
			1u,
			bufferPtr.GetAddressOf(),
			&stride,
			&offset
		);
	}



	// DxIBuffer
	DxIBuffer::DxIBuffer(
		ID3D11Device* devicePtr,
		ID3D11DeviceContext* deviceContextPtr,
		uint32_t* indices,
		LzSizeT indexCount
	) : Bindable(LZ_BIND_TYPE_IBUFF, indexCount),
		devicePtr(devicePtr),
		deviceContextPtr(deviceContextPtr),
		indexCount(indexCount),
		bufferPtr(nullptr)
	{
		LZ_RUNTIME_GUARD((devicePtr && deviceContextPtr), "[DxBuffer] Device and device context must not be NULL");
		D3D11_BUFFER_DESC desc{ 0 };
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(uint32_t) * indexCount;
		desc.CPUAccessFlags = 0u;
		desc.MiscFlags = 0u;
		desc.StructureByteStride = sizeof(uint32_t);

		D3D11_SUBRESOURCE_DATA subresc{ 0 };
		subresc.pSysMem = indices;

		auto result = devicePtr->CreateBuffer(
			&desc,
			&subresc,
			&bufferPtr
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());
	}

	void DxIBuffer::bind() {
		LZ_RUNTIME_GUARD((devicePtr && deviceContextPtr), "[DxBuffer] Device and device context must not be NULL");
		deviceContextPtr->IASetIndexBuffer(
			bufferPtr.Get(),
			DXGI_FORMAT_R32_UINT,
			0u
		);
	}



	// DxBufferLayout
	DxBufferLayout::DxBufferLayout(
		ID3D11Device* devicePtr,
		ID3D11DeviceContext* deviceContextPtr,
		VertexAttribute* attributes,
		LzSizeT attribCount,
		ID3DBlob* vBlob
	) : Bindable(LZ_BIND_TYPE_LAYOUT, -1),
		devicePtr(devicePtr),
		deviceContextPtr(deviceContextPtr),
		inputLayoutPtr(nullptr)
	{
		D3D11_INPUT_ELEMENT_DESC desc[attribCount];

		for (auto index = 0u; index < attribCount; ++index) {
			desc[index].SemanticName = attributes[index].name.c_str();
			desc[index].SemanticIndex = 0u;
			desc[index].Format = getFormatForPrimitiveType(attributes[index].type);
			desc[index].InputSlot = 0u;
			desc[index].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			desc[index].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			desc[index].InstanceDataStepRate = 0u;
		}

		auto result = devicePtr->CreateInputLayout(
			desc,
			attribCount,
			vBlob->GetBufferPointer(),
			vBlob->GetBufferSize(),
			&inputLayoutPtr
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());
	}

	void DxBufferLayout::bind() {
		LZ_RUNTIME_GUARD((devicePtr && deviceContextPtr), "[DxBuffer] Device and device context must not be NULL");
		deviceContextPtr->IASetInputLayout(inputLayoutPtr.Get());
	}

	DXGI_FORMAT DxBufferLayout::getFormatForPrimitiveType(PrimitiveType type) {
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
};

#endif
