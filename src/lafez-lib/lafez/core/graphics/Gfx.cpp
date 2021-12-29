#include "Gfx.hpp"
#include "Drawable.hpp"
#include <lafez/misc/lafez_exception.hpp>

namespace Lafez {
	Gfx* Gfx::shared = nullptr;
	const unsigned int Gfx::MODEL_BUFFER_INDEX = 0u;
	const unsigned int Gfx::VIEW_BUFFER_INDEX = 1u;
	const unsigned int Gfx::PROJECTION_BUFFER_INDEX = 2u;

	Gfx* Gfx::gfx() {
		//LZ_RUNTIME_GUARD(shared, "ERROR: GFX NOT INITIALIZED");
		return shared;
	}

	void Gfx::shutDown() {
		LZ_RUNTIME_GUARD(shared, "ERROR: GFX NOT INITIALIZED");
		delete shared;
	}
};