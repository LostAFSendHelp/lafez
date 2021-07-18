#ifdef __LZ_WIN

#include <lafez/core/foundation/ImGuiBackend.hpp>
#include <wrl.h>
#include <d3d11.h>
#include <Windows.h>
#include <lafez-imgui/impl/imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using Microsoft::WRL::ComPtr;

namespace Lafez {
	class DxImGui : public ImGuiBackend {
	public:
		DxImGui(HWND hWnd, const ComPtr<ID3D11Device>& devicePtr, const ComPtr<ID3D11DeviceContext>& deviceContextPtr);
		DxImGui(const DxImGui& other) = delete;
		DxImGui(DxImGui&& other) = delete;
		~DxImGui();

		DxImGui& operator=(const DxImGui& other) = delete;
		DxImGui& operator=(DxImGui&& other) = delete;

	protected:
		void initImpl() override;
		void terminateImpl() override;
		void newFrameImpl() override;
		void renderDrawDataImpl(ImDrawData* data) override;

	private:
		ComPtr<ID3D11Device> mDevicePtr;
		ComPtr<ID3D11DeviceContext> mDeviceContextPtr;
		HWND mHandleToWindow;
	};
};

#endif // __LZ_WIN
