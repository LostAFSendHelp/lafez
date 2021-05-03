#pragma once
#ifdef __LZ_WIN

#include <d3d11.h>
#include <wrl.h>
#include <lafez/lafez_pch.hpp>

using Microsoft::WRL::ComPtr;

namespace Lafez {
	class DxShaderContainer {
	public:

		/**
		 * @brief Construct a DxShaderContainer object, containing a vertex shader and a pixel shader
		 * @param vShaderPtr the ComPtr to the vertex shader
		 * @param pShaderPtr the ComPtr to the pixel Shader
		 */
		DxShaderContainer(const ComPtr<ID3D11VertexShader>& vShaderPtr, const ComPtr<ID3D11PixelShader>& pShaderPtr, const ComPtr<ID3DBlob>& pBlobPtr);
		DxShaderContainer(const DxShaderContainer& other) = delete;
		DxShaderContainer(DxShaderContainer&& other) = delete;



		/**
		 * @brief Destroy the DxShaderContainer object
		 */
		~DxShaderContainer() = default;



		/**
		 * @brief Get a ComPtr to the vertex shader
		 */
		ComPtr<ID3D11VertexShader> getVertexShaderPtr() const;



		/**
		 * @brief Get a ComPtr to the pixel shader
		 */
		ComPtr<ID3D11PixelShader> getPixelShaderPtr() const;



		/**
		 * @brief Get a ComPtr to the vertex shader blob shader
		 */
		ComPtr<ID3DBlob> getShaderBlobPtr() const;



		/**
		 * @brief Get the number of shaders created so far, used for Shader object IDs
		 */
		static uint16_t getCount();

	private:
		/// ComPtr to the vertex shader
		ComPtr<ID3D11VertexShader> mVertexShaderPtr;
		/// ComPtr to the pixel shader
		ComPtr<ID3D11PixelShader> mPixelShaderPtr;
		// TODO: check if this could be used without storing
		/// ComPtr to the vertex shader blob
		ComPtr<ID3DBlob> mBlobPtr;

		/// The number of shaders created, also used for Shader id
		static uint32_t sCount;
	};
};

#endif
