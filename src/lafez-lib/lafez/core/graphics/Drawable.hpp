#pragma once
#include <lafez/lafez_pch.hpp>
#include "Bindable.hpp"
#include "Gfx.hpp"

namespace Lafez {
	class LAFEZLIB Drawable final {
	public:
		const uint32_t id;

		Drawable(Gfx* const gfx);
		Drawable(const Drawable& other) = delete;
		Drawable(Drawable&& other) = delete;
		~Drawable() noexcept;

		Drawable& operator=(const Drawable& other) = delete;
		Drawable& operator=(Drawable&& other) = delete;

		void draw();
		void addBindable(const LzShrPtr<Bindable>& bindable);

	private:
		static uint32_t count;

		Gfx* const gfx;
		LzSizeT indexCount;
		LzSizeT vertexCount;
		LzVec<LzShrPtr<Bindable>> bindables;
	};
};