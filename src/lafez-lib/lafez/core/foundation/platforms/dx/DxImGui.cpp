#ifdef __LZ_WIN

#include "DxImGui.hpp"
#include <lafez/utils/Log.hpp>
#include <lafez-imgui/impl/imgui_impl_win32.h>
#include <lafez-imgui/impl/imgui_impl_dx11.h>

namespace Lafez {
	DxImGui::DxImGui(
		HWND hWnd,
		const ComPtr<ID3D11Device>& devicePtr,
		const ComPtr<ID3D11DeviceContext>& deviceContextPtr
	) :
		mHandleToWindow(hWnd),
		mDevicePtr(devicePtr),
		mDeviceContextPtr(deviceContextPtr)
	{
		LZ_ENGINE_ASSERT(
			mHandleToWindow && 
			mDevicePtr &&
			mDeviceContextPtr,
			"ATTEMPTING TO INITIALIZE DX IMGUI TO NULLPTR"
		);
	}

	DxImGui::~DxImGui() {
		terminateImpl();
	}

	void DxImGui::initImpl() {
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(mHandleToWindow);
		ImGui_ImplDX11_Init(mDevicePtr.Get(), mDeviceContextPtr.Get());
		LZ_ENGINE_INFO("DX IMGUI INITIALIZED");
	}

	void DxImGui::terminateImpl() {
		if (ImGui::GetCurrentContext() != nullptr) {
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
			LZ_ENGINE_INFO("DX IMGUI TERMINATED");
		}
	}

	void DxImGui::newFrameImpl() {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
	}

	void DxImGui::renderDrawDataImpl(ImDrawData* data) {
		ImGui_ImplDX11_RenderDrawData(data);
	}
};

#endif // __LZ_WIN
