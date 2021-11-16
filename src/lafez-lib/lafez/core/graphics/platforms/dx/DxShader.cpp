#ifdef __LZ_WIN

#include "DxShader.hpp"
#include <d3dcompiler.h>
#include <lafez/misc/lafez_exception.hpp>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Lafez {
	DxShader::DxShader(
		ID3D11Device* devicePtr,
		ID3D11DeviceContext* deviceContextPtr,
		const LzString& name,
		const LzString& vSource,
		const LzString& pSource
	) : Bindable(LZ_BIND_TYPE_SHADER, -1),
		name(name),
		vShaderPtr(nullptr),
		pShaderPtr(nullptr),
		vShaderBlobPtr(nullptr),
		devicePtr(devicePtr),
		deviceContextPtr(deviceContextPtr)
	{
		LZ_RUNTIME_GUARD((devicePtr && deviceContextPtr), "Device and device context must not be NULL");
		
		auto flags = D3DCOMPILE_ENABLE_STRICTNESS;
		ComPtr<ID3DBlob> vBlob, pBlob, eBlob;

		#ifdef __LZ_DEBUG
		flags != D3DCOMPILE_DEBUG;
		#endif

		LZ_RUNTIME_GUARD(
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
					0u,
					&vBlob,
					&eBlob
				)
			),
			(char*)eBlob->GetBufferPointer()
		);

		LZ_RUNTIME_GUARD(
			SUCCEEDED(
				D3DCompile(
					pSource.c_str(),
					pSource.size(),
					nullptr,
					nullptr,
					nullptr,
					"ps_main",
					"ps_5_0",
					flags,
					0u,
					&pBlob,
					&eBlob
				)
			),
			(char*)eBlob->GetBufferPointer()
		);

		auto result = devicePtr->CreateVertexShader(
			vBlob->GetBufferPointer(),
			vBlob->GetBufferSize(),
			nullptr,
			&vShaderPtr
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());

		result = devicePtr->CreatePixelShader(
			pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(),
			nullptr,
			&pShaderPtr
		);

		LZ_RUNTIME_GUARD(SUCCEEDED(result), WinException::translateErrorCode(result).c_str());

		vShaderBlobPtr = vBlob;
	}

	void DxShader::bind() {
		LZ_RUNTIME_GUARD((devicePtr && deviceContextPtr), "Device and device context must not be NULL");

		deviceContextPtr->VSSetShader(vShaderPtr.Get(), nullptr, 0u);
		deviceContextPtr->PSSetShader(pShaderPtr.Get(), nullptr, 0u);
	}

	ID3DBlob* DxShader::getVBlob() const {
		return vShaderBlobPtr.Get();
	}
};

#endif