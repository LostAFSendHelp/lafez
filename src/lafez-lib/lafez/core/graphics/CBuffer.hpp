#pragma once
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>

namespace Lafez {
	class LAFEZLIB CBuffer {
	public:
		virtual void updateData(const void* data, LzSizeT size) = 0;
		virtual void bind() = 0;
	};
};