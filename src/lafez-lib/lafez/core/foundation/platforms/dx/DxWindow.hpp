#pragma once
#ifdef __LZ_WIN

#include <lafez/core/foundation/Window.hpp>
#include <lafez/core/foundation/WindowInfo.hpp>
#include <Windows.h>

namespace Lafez {
	class DxWindow final : public Window {
	public:
		DxWindow(const char* name, uint16_t width, uint16_t height);
		~DxWindow();

		uint16_t getWidthImpl() const override;
		uint16_t getHeightImpl() const override;
		const LzString& getNameImpl() const override;
		void setNameImpl(const char* name) override;
		bool shouldCloseImpl() const override;

		void initImpl() override;
		void terminateImpl() override;
		void updateImpl() override;
		void closeImpl() override;

		void* getWindowPointerImpl() const override;

	private:
		HWND mHandleToWindow;
		WNDCLASSEX* mWindowClass;

		WNDCLASSEX* getWindowClass();
		LRESULT handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static HINSTANCE sHandleToInstance;

		static LRESULT WINAPI windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI windowProcThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
};

#endif