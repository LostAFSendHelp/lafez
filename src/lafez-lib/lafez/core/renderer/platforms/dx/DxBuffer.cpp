#ifdef __LZ_WIN

#include "DxBuffer.hpp"

namespace Lafez {
	uint32_t DxBuffer::sCount = 0;

	DxBuffer::DxBuffer(const ComPtr<ID3D11Buffer>& bufferPtr) :
		mBufferPtr(bufferPtr) {
		++sCount;
	}

	ComPtr<ID3D11Buffer> DxBuffer::getBufferPtr() const {
		return mBufferPtr;
	}

	uint32_t DxBuffer::getCount() {
		return sCount;
	}
};


#endif