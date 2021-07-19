/**
 * Contains the entry point to be used in client app,
 * make sure to have this main function in one and one
 * translation unit only for the entry point to the app
 * and to avoid conflicting definitions.
 */

#pragma once
#include "Application.hpp"
#include <lafez/utils/Log.hpp>
#include <lafez/misc/lafez_exception.hpp>

//#ifdef __LZ_WIN
//	#include <Windows.h>
//#endif

#ifdef __LZ_WIN

// for windows
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR pScmdline,
	int iCmdshow) {

	auto application = Lafez::createApplication();
	LZ_ENGINE_GUARD_VAL(application, 0, "APPLICATION NOT INITIALIZED");
	LZ_ENGINE_INFO("LAFEZ ENGINE - WINDOW BUILD");

	try {
		application->startUp();
		application->run();
		application->shutDown();
	} catch (const Lafez::WinException& e) {
		MessageBox(nullptr, e.what(), "Run-time exception", MB_OK | MB_ICONERROR);
	} catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Run-time exception", MB_OK | MB_ICONERROR);
	}

	return 0;
}

#else

// for non-windows systems
int main() {
	auto application = Lafez::createApplication();
	LZ_ENGINE_GUARD_VAL(application, 0, "APPLICATION NOT INITIALIZED");
	LZ_ENGINE_INFO("LAFEZ ENGINE - NON-WINDOW BUILD");

	application->startUp();
	application->run();
	application->shutDown();

	return 0;
}

#endif
