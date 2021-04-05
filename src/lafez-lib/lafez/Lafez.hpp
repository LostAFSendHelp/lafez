/**
 * Contains the entry point to be used in client app,
 * make sure to have this main function in one and one
 * translation unit only for the entry point to the app
 * and to avoid conflicting definitions.
 */

#pragma once
#include "Application.hpp"
#include <lafez/utils/Log.hpp>

int main() {
	auto application = Lafez::createApplication();
	LZ_ENGINE_GUARD_VAL(application, 0, "APPLICATION NOT INITIALIZED");

	application->startUp();
	application->run();
	application->shutDown();

	return 0;
}