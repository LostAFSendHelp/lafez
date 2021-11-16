#pragma once
#include <lafez/core/graphics/Bindable.hpp>

namespace Lafez {
	class GlShader final : public Bindable {
	public:
		const LzString name;

		GlShader(const LzString& name, const LzString& vSource, const LzString& pSource);
		GlShader(const GlShader& other) = delete;
		GlShader(GlShader&& other) = delete;
		~GlShader() = default;

		GlShader& operator = (const GlShader& other) = delete;
		GlShader& operator = (GlShader&& other) = delete;

		void bind() override;
		uint32_t getShaderId() const;

	private:
		uint32_t shaderId;
		static uint32_t createShader(uint32_t type, const LzString& source);
	};
};