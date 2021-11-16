#pragma once
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>

#define LZ_BIND_TYPE_VBUFF		::Lafez::BindType::VertexBuffer
#define LZ_BIND_TYPE_IBUFF		::Lafez::BindType::IndexBuffer
#define LZ_BIND_TYPE_LAYOUT		::Lafez::BindType::BufferLayout
#define LZ_BIND_TYPE_SHADER		::Lafez::BindType::Shader
#define LZ_BIND_TYPE_NONE		::Lafez::BindType::None

namespace Lafez {
	enum class BindType {
		VertexBuffer,
		IndexBuffer,
		BufferLayout,
		Shader,
		None
	};

	class LAFEZLIB Bindable {
	public:
		friend class Drawable;

		const uint32_t id;
		const BindType bindType;
		const int customBindValue;

		Bindable(const Bindable& other) = delete;
		Bindable(Bindable&& other) = delete;
		virtual ~Bindable() noexcept = default;

		Bindable& operator=(const Bindable& other) = delete;
		Bindable& operator=(Bindable&& other) = delete;

	protected:
		Bindable(BindType bindType, int customBindValue) noexcept;
		virtual void bind() = 0;

	private:
		static uint32_t count;
	};
};