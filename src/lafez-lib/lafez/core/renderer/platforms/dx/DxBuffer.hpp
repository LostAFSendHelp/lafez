#pragma once
#ifdef __LZ_WIN

#include <d3d11.h>
#include <wrl.h>
#include <lafez/lafez_pch.hpp>

using Microsoft::WRL::ComPtr;

namespace Lafez {
	class DxBuffer {
	public:
		DxBuffer(const ComPtr<ID3D11Buffer>& bufferPtr);
		DxBuffer(const DxBuffer& other) = delete;
		DxBuffer(DxBuffer&& other) = delete;
		~DxBuffer() = default;

		ComPtr<ID3D11Buffer> getBufferPtr() const;

		static uint32_t getCount();

	private:
		ComPtr<ID3D11Buffer> mBufferPtr;

		static uint32_t sCount;
	};
};

#endif