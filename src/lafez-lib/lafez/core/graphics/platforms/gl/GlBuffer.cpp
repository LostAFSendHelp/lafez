#include <lafez/platform_headers/lafez_gl.hpp>
#include <lafez/misc/lafez_exception.hpp>
#include <lafez/utils/Log.hpp>
#include "GlBuffer.hpp"

namespace Lafez {
	
	// vertex buffer
	GlVBuffer::GlVBuffer(
		float* data,
		LzSizeT dataSize,
		LzSizeT vertexCount
	) :
		Bindable(LZ_BIND_TYPE_VBUFF, vertexCount),
		bufferId(0u),
		vertexCount(vertexCount)
	{
		LZ_GLCALL(
			glGenBuffers(1, &bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0u);
		);
	}

	void GlVBuffer::bind() {
		LZ_GLCALL(
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		);
	}

	uint32_t GlVBuffer::getBufferId() const {
		return bufferId;
	}



	// index buffer
	GlIBuffer::GlIBuffer(
		uint32_t* indices,
		LzSizeT indexCount
	) :
		Bindable(LZ_BIND_TYPE_IBUFF, indexCount),
		bufferId(0u),
		indexCount(indexCount)
	{
		LZ_GLCALL(
			glGenBuffers(1, &bufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indexCount, indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
		);
	}

	void GlIBuffer::bind() {
		LZ_GLCALL(
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
		);
	}

	uint32_t GlIBuffer::getBufferId() const {
		return bufferId;
	}



	// buffer layout
	GlBufferLayout::GlBufferLayout(
		VertexAttribute* attributes,
		LzSizeT attribCount
	) :
		Bindable(LZ_BIND_TYPE_LAYOUT, -1),
		attributes(),
		elementStride(0)
	{
		LZ_RUNTIME_GUARD(attributes, "VertexAttribute array must not be NULL");

		for (auto index = 0u; index < attribCount; ++index) {
			this->attributes.emplace_back(attributes[index], index);
			elementStride += this->attributes[index].size;
		}
	}

	void GlBufferLayout::bind() {
		LzSizeT offset = 0;
		for (const auto& attrib : attributes) {
			LZ_GLCALL(
				glVertexAttribPointer(
					attrib.index,
					attrib.elementSize,
					attrib.glType,
					GL_FALSE,
					elementStride,
					(void*)offset
				);

				glEnableVertexAttribArray(attrib.index);
				offset += attrib.size;
			);
		}
	}


	// vertex attribute
	GlVertexAttribute::GlVertexAttribute(
		const VertexAttribute& attribute,
		uint32_t index
	) :
		index(index),
		size(getSizeFor(attribute.type)),
		elementSize(getElementSizeFor(attribute.type)),
		glType(getGlTypeForPrimitiveType(attribute.type))
	{

	}

	GlVertexAttribute::GlVertexAttribute(const GlVertexAttribute& other) :
		index(other.index),
		size(other.size),
		elementSize(other.elementSize),
		glType(other.glType)
	{

	}

	GlVertexAttribute::GlVertexAttribute(GlVertexAttribute&& other) :
		index(other.index),
		size(other.size),
		elementSize(other.elementSize),
		glType(other.glType)
	{

	}

	uint32_t GlVertexAttribute::getGlTypeForPrimitiveType(PrimitiveType type) {
		switch (type) {
		case LZ_PTYPE_INT:
		case LZ_PTYPE_VEC2I:
		case LZ_PTYPE_VEC3I:
		case LZ_PTYPE_VEC4I:
			return GL_INT;

		case LZ_PTYPE_FLOAT:
		case LZ_PTYPE_VEC2F:
		case LZ_PTYPE_VEC3F:
		case LZ_PTYPE_VEC4F:
			return GL_FLOAT;

		default: {
			LZ_RUNTIME_GUARD(false, "PRIMITIVE TYPE [NONE] IS NOT SUPPORTED");
			return 0;
		}
		}
	}

	LzSizeT GlVertexAttribute::getSizeFor(PrimitiveType type) {
		switch (type) {
		case LZ_PTYPE_INT:      return sizeof(int32_t);
		case LZ_PTYPE_VEC2I:    return sizeof(int32_t) * 2;
		case LZ_PTYPE_VEC3I:    return sizeof(int32_t) * 3;
		case LZ_PTYPE_VEC4I:    return sizeof(int32_t) * 4;
		case LZ_PTYPE_FLOAT:    return sizeof(float);
		case LZ_PTYPE_VEC2F:    return sizeof(float) * 2;
		case LZ_PTYPE_VEC3F:    return sizeof(float) * 3;
		case LZ_PTYPE_VEC4F:    return sizeof(float) * 4;

		default: {
			LZ_RUNTIME_GUARD(false, "PRIMITIVE TYPE [NONE] IS NOT SUPPORTED");
			return 0;
		}
		}
	}

	LzSizeT GlVertexAttribute::getElementSizeFor(PrimitiveType type) {
		switch (type) {
		case LZ_PTYPE_FLOAT:
		case LZ_PTYPE_INT:
			return 1;

		case LZ_PTYPE_VEC2F:
		case LZ_PTYPE_VEC2I:
			return 2;

		case LZ_PTYPE_VEC3F:
		case LZ_PTYPE_VEC3I:
			return 3;

		case LZ_PTYPE_VEC4F:
		case LZ_PTYPE_VEC4I:
			return 4;

		default: {
			LZ_RUNTIME_GUARD(false, "PRIMITIVE TYPE [NONE] IS NOT SUPPORTED");
			return 0;
		}
		}
	}
};