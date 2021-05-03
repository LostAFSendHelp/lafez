#ifdef __LZ_WIN

#include "DxShaderContainer.hpp"

using Microsoft::WRL::ComPtr;

namespace Lafez {
	uint32_t DxShaderContainer::sCount = 0;

	DxShaderContainer::DxShaderContainer(const ComPtr<ID3D11VertexShader>& vShaderPtr, const ComPtr<ID3D11PixelShader>& pShaderPtr, const ComPtr<ID3DBlob>& blobPtr):
		mVertexShaderPtr(vShaderPtr),
		mPixelShaderPtr(pShaderPtr),
		mBlobPtr(blobPtr) {
		++sCount;
	}

	ComPtr<ID3D11VertexShader> DxShaderContainer::getVertexShaderPtr() const {
		return mVertexShaderPtr;
	}

	ComPtr<ID3D11PixelShader> DxShaderContainer::getPixelShaderPtr() const {
		return mPixelShaderPtr;
	}

	ComPtr<ID3DBlob> DxShaderContainer::getShaderBlobPtr() const {
		return mBlobPtr;
	}

	uint16_t DxShaderContainer::getCount() {
		return sCount;
	}
};

#endif