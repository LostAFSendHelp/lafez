#include "DxWindow.hpp"
#include <lafez/core/lafez_event.hpp>
#include <windowsx.h>
#include <lafez/core/lafez_renderer.hpp>
#include <lafez/misc/lafez_exception.hpp>

#ifdef __LZ_WIN

namespace Lafez {
	HINSTANCE DxWindow::sHandleToInstance = GetModuleHandleA(nullptr);

	DxWindow::DxWindow(
		const char* name,
		uint16_t width,
		uint16_t height,
		WndProcThunk wndProcThunk
	):
		Window(name, width, height),
		mHandleToWindow(nullptr),
		mWindowClass(nullptr),
		mWndProcThunk(wndProcThunk)
	{
		
	}

	DxWindow::~DxWindow() {
		LZ_ENGINE_INFO("DX WINDOW DESTROYED");
	}

	uint16_t DxWindow::getWidthImpl() const {
		return mWindowInfo->mWidth;
	}

	uint16_t DxWindow::getHeightImpl() const {
		return mWindowInfo->mHeight;
	}

	const LzString& DxWindow::getNameImpl() const {
		return mWindowInfo->mName;
	}

	void DxWindow::setNameImpl(const char* name) {
		mWindowInfo->mName = name;
		
		if (mHandleToWindow) {
			SetWindowText(mHandleToWindow, name);
		}
	}

	bool DxWindow::shouldCloseImpl() const {
		return mWindowInfo->mShouldClose;
	}

	void DxWindow::initImpl() {
		RECT windowRect;
		windowRect.top = 100;
		windowRect.left = 100;
		windowRect.bottom = 100 + mWindowInfo->mHeight;
		windowRect.right = 100 + mWindowInfo->mWidth;

		DWORD windowStyles = WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME | WS_CAPTION;
		if (!AdjustWindowRectEx(
			&windowRect,
			windowStyles,
			FALSE,
			NULL
		)) {
			throw LZ_WINEXCEPT_LAST;
		}

		mHandleToWindow = CreateWindowEx(
			NULL,								// no extended styles
			getWindowClass()->lpszClassName,	// class name
			mWindowInfo->mName.c_str(),			// window name
			windowStyles,						// styles
			windowRect.left,					// x
			windowRect.left,					// y
			windowRect.right - windowRect.left,	// width
			windowRect.bottom - windowRect.top,	// height
			nullptr,							// parent						
			nullptr,							// menu
			getWindowClass()->hInstance,		// hInstance
			this								// user pointer
		);

		if (!mHandleToWindow) {
			throw LZ_WINEXCEPT_LAST;
		}

		GetClientRect(mHandleToWindow, &windowRect);

		LZ_ENGINE_INFO(
			"WINDOW: {0} x {1}, at ({2}, {3})",
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			windowRect.left,
			windowRect.top
		);
		
		ShowWindow(mHandleToWindow, SW_NORMAL);
	}

	void DxWindow::terminateImpl() {
		// only initImpl initializes both pointers, so the 2 are guaranteed to share the NULL-ness
		// also make sure to call `close` before terminating so the window is destroyed properly
		if (mHandleToWindow || mWindowClass) {
			UnregisterClass(getWindowClass()->lpszClassName, getWindowClass()->hInstance);
			mHandleToWindow = nullptr;
			mWindowClass = nullptr;
			LZ_ENGINE_INFO("DX WINDOW TERMINATED");
		}
	}

	void DxWindow::updateImpl() {
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				// if msg is WM_QUIT, notify the game loop so it stops
				mWindowInfo->mShouldClose = true;
			} else {
				// if PeekMessage does not return 0, i.e not WM_QUIT
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	void DxWindow::closeImpl() {
		if (mHandleToWindow == nullptr) {
			LZ_ENGINE_WARN("ABORTING ATTEMPT TO CLOSE UNINITIALIZED WINDOW...");
		}

		// close the window and post WM_DESTROY message to the queue
		LZ_ENGINE_ASSERT(DestroyWindow(mHandleToWindow), "Failed to destroy window");
	}

	void* DxWindow::getWindowPointerImpl() const {
		return mHandleToWindow;
	}

	LRESULT DxWindow::handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		// TODO: handle or delegate errors from here

		if (mWndProcThunk && mWndProcThunk(hWnd, uMsg, wParam, lParam)) {
			return true;
		}

		switch (uMsg) {

		case WM_CLOSE: {
			/* notify the client app of the close attempt
			 the client app is to decide whether to quit */
			WindowCloseEvent event{ };
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_DESTROY: {
			// notify the message loop about the close event
			PostQuitMessage(0);
			return 0;
		}

		case WM_KEYDOWN: {
			LZ_ENGINE_GUARD_VAL(
				(wParam >= 0),
				DefWindowProc(hWnd, uMsg, wParam, lParam),
				"KEY NOT RECOGNIZED"
			);

			if (HIWORD(lParam) & KF_REPEAT) {
				KeyEvent event(wParam, LZ_BUTTON_REPEAT); // wParam: implicit conversion is Safe as virtual keycodes max out as 1 byte
				EventCenter::getInstance()->emit(event);
			} else {
				KeyEvent event(wParam, LZ_BUTTON_PRESS);
				EventCenter::getInstance()->emit(event);
			}

			return 0;
		}

		case WM_KEYUP: {
			LZ_ENGINE_GUARD_VAL(
				(wParam >= 0),
				DefWindowProc(hWnd, uMsg, wParam, lParam),
				"KEY NOT RECOGNIZED"
			);

			KeyEvent event(wParam, LZ_BUTTON_RELEASE);
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_SIZE: {
			auto width = LOWORD(lParam), height = HIWORD(lParam);
			WindowResizeEvent event(width, height);
			if (RendererBackend::isInitialized()) {
				RendererBackend::setViewport(0, 0, width, height);
			}
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_MOUSEMOVE: {
			MouseMoveEvent event((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_LBUTTONDOWN: {
			SetCapture(mHandleToWindow);
			MouseButtonEvent event(LZ_MOUSE_LEFT, LZ_BUTTON_PRESS);
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_LBUTTONUP: {
			ReleaseCapture();
			MouseButtonEvent event(LZ_MOUSE_LEFT, LZ_BUTTON_RELEASE);
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_RBUTTONDOWN: {
			SetCapture(mHandleToWindow);
			MouseButtonEvent event(LZ_MOUSE_RIGHT, LZ_BUTTON_PRESS);
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_RBUTTONUP: {
			ReleaseCapture();
			MouseButtonEvent event(LZ_MOUSE_RIGHT, LZ_BUTTON_RELEASE);
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_MBUTTONDOWN: {
			SetCapture(mHandleToWindow);
			MouseButtonEvent event(LZ_MOUSE_MID, LZ_BUTTON_PRESS);
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_MBUTTONUP: {
			ReleaseCapture();
			MouseButtonEvent event(LZ_MOUSE_MID, LZ_BUTTON_RELEASE);
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		case WM_MOUSEWHEEL: {
			MouseScrollEvent event(GET_WHEEL_DELTA_WPARAM(wParam));
			EventCenter::getInstance()->emit(event);
			return 0;
		}

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	WNDCLASSEX* DxWindow::getWindowClass() {
		LZ_ENGINE_ASSERT(sHandleToInstance, "HANDLE TO APP INSTANCE MUST NOT BE NULL");
		
		if (!mWindowClass) {
			const char* className = "LafezDxWindow";
			mWindowClass = new WNDCLASSEX;
			ZeroMemory(mWindowClass, sizeof(WNDCLASSEX));

			mWindowClass->cbSize = sizeof(WNDCLASSEX);
			mWindowClass->hInstance = sHandleToInstance;
			mWindowClass->lpszClassName = className;
			mWindowClass->style = CS_OWNDC;
			mWindowClass->lpfnWndProc = windowProc;
			mWindowClass->hCursor = nullptr;
			mWindowClass->hbrBackground = nullptr;
			RegisterClassEx(mWindowClass);
		}

		return mWindowClass;
	}

	LRESULT WINAPI DxWindow::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		// when window is created
		if (uMsg == WM_NCCREATE) {
			// extra param sent together with the create message, contains user pointer
			auto userPtr = reinterpret_cast<CREATESTRUCT*>(lParam);
			// re-cast user pointer back to this class
			auto winPtr = reinterpret_cast<DxWindow*>(userPtr->lpCreateParams);
			// attach user pointer to window to be retrieved internally in the window class
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(winPtr));
			// replace WinProc func of window: past this point all messages to this window go through the thunk instead
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&DxWindow::windowProcThunk));
			return winPtr->handleMessages(hWnd, uMsg, wParam, lParam);
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT WINAPI DxWindow::windowProcThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		// retrieve attached user pointer, which is the DxWindow container of the window
		auto userPtr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
		auto winPtr = reinterpret_cast<DxWindow*>(userPtr);

		// pass the message to the member function instead
		return winPtr->handleMessages(hWnd, uMsg, wParam, lParam);
	}

}

#endif