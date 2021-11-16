#pragma once
#ifdef __LZ_WIN

#include <lafez/core/graphics/Bindable.hpp>
#include <wrl.h>
#include <d3d11.h>

using Microsoft::WRL::ComPtr;

namespace Lafez {
	class DxShader final : public Bindable {
	public:
		const LzString name;

		DxShader(ID3D11Device* devicePtr, ID3D11DeviceContext* deviceContextPtr, const LzString& name, const LzString& vSource, const LzString& pSource);
		DxShader(const DxShader& other) = delete;
		DxShader(DxShader&& other) = delete;
		~DxShader() = default;

		DxShader& operator = (const DxShader& other) = delete;
		DxShader& operator = (DxShader&& other) = delete;

		void bind() override;
		ID3DBlob* getVBlob() const;

	private:
		ComPtr<ID3D11VertexShader> vShaderPtr;
		ComPtr<ID3D11PixelShader> pShaderPtr;
		ComPtr<ID3DBlob> vShaderBlobPtr;
		ID3D11Device* devicePtr;
		ID3D11DeviceContext* deviceContextPtr;
	};
};

#endif