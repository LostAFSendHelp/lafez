#pragma once
#include <lafez/core/graphics/Bindable.hpp>
#include <lafez/core/graphics/VertexAttribute.hpp>

namespace Lafez {
	
	// vertex buffer
	class GlVBuffer final : public Bindable {
	public:
		const LzSizeT vertexCount;

		GlVBuffer(float* data, LzSizeT dataSize, LzSizeT vertexCount);
		GlVBuffer(const GlVBuffer& other) = delete;
		GlVBuffer(GlVBuffer&& other) = delete;
		~GlVBuffer() = default;

		GlVBuffer& operator = (const GlVBuffer& other) = delete;
		GlVBuffer& operator = (GlVBuffer&& other) = delete;

		void bind() override;
		uint32_t getBufferId() const;

	private:
		uint32_t bufferId;
	};



	// index buffer
	class GlIBuffer final : public Bindable {
	public:
		const LzSizeT indexCount;

		GlIBuffer(uint32_t* indices, LzSizeT indexCount);
		GlIBuffer(const GlIBuffer& other) = delete;
		GlIBuffer(GlIBuffer&& other) = delete;
		~GlIBuffer() = default;

		GlIBuffer& operator = (const GlIBuffer& other) = delete;
		GlIBuffer& operator = (GlIBuffer&& other) = delete;

		void bind() override;
		uint32_t getBufferId() const;

	private:
		uint32_t bufferId;
	};



	// vertex attribute
	struct GlVertexAttribute {
	public:
		const uint32_t index;
		const LzSizeT size;
		const LzSizeT elementSize;
		const uint32_t glType;

		GlVertexAttribute(const VertexAttribute& attribute, uint32_t index);
		GlVertexAttribute(const GlVertexAttribute& other);
		GlVertexAttribute(GlVertexAttribute&& other);
		~GlVertexAttribute() = default;

		GlVertexAttribute& operator = (const GlVertexAttribute& other) = delete;
		GlVertexAttribute& operator = (GlVertexAttribute&& other) = delete;

	private:
		static uint32_t getGlTypeForPrimitiveType(PrimitiveType type);
		static LzSizeT getSizeFor(PrimitiveType type);
		static LzSizeT getElementSizeFor(PrimitiveType type);
	};



	// buffer layout
	class GlBufferLayout final : public Bindable {
	public:
		GlBufferLayout(VertexAttribute* attributes, LzSizeT attribCount);
		GlBufferLayout(const GlBufferLayout& other) = delete;
		GlBufferLayout(GlBufferLayout&& other) = delete;
		~GlBufferLayout() = default;

		GlBufferLayout& operator = (const GlBufferLayout& other) = delete;
		GlBufferLayout& operator = (GlBufferLayout&& other) = delete;

		void bind() override;

	private:
		LzVec<GlVertexAttribute> attributes;
		LzSizeT elementStride;
	};
};