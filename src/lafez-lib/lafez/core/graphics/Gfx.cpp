#include "Gfx.hpp"
#include <lafez/misc/lafez_exception.hpp>

namespace Lafez {
	Gfx* Gfx::shared = nullptr;

	Gfx* Gfx::gfx() {
		//LZ_RUNTIME_GUARD(shared, "ERROR: GFX NOT INITIALIZED");
		return shared;
	}

	void Gfx::shutDown() {
		LZ_RUNTIME_GUARD(shared, "ERROR: GFX NOT INITIALIZED");
		delete shared;
	}
};