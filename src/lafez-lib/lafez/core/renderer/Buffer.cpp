#include <lafez/utils/Log.hpp>
#include <lafez/core/renderer/RendererBackend.hpp>
#include "Buffer.hpp"

namespace Lafez {

    /********************************************************
    *                   VertexBufferLayout                  *
    ********************************************************/

    VertexAttribute::VertexAttribute(const LzString& name, PrimitiveType type):
        mName(name),
        mType(type),
        mIndex(0),
        mSize(0),
        mElementSize(0),
        mStride(0),
        mOffset(0) {

    }

    VertexAttribute::VertexAttribute(const VertexAttribute& other) :
        mName(other.mName),
        mType(other.mType),
        mIndex(other.mIndex),
        mSize(other.mSize),
        mElementSize(other.mElementSize),
        mStride(other.mStride),
        mOffset(other.mOffset) {

    }

    VertexAttribute& VertexAttribute::operator=(const VertexAttribute& other) {
        mName = other.mName;
        mType = other.mType;
        mIndex = other.mIndex;
        mSize = other.mSize;
        mElementSize = other.mElementSize;
        mStride = other.mStride;
        mOffset = other.mOffset;
        return *this;
    }

    const LzString& VertexAttribute::getName() const {
        return mName;
    }

    VertexBufferLayout::VertexBufferLayout(const LzVec<VertexAttribute>& attributes):
    mAttributes(attributes) {
        uint8_t iteration = 0;
        LzSizeT offset = 0;
        LzSizeT stride = 0;

        for (auto& attrib : mAttributes) {
            auto type = attrib.mType;
            attrib.mIndex = iteration;
            attrib.mElementSize = getElementSizeFor(type);
            attrib.mOffset = stride;
            attrib.mType = type;
            attrib.mSize = getSizeFor(type);

            stride += attrib.mSize;
            ++iteration;
        }

        for (auto& attrib : mAttributes) {
            attrib.mStride = stride;
        }
    }

    const LzVec<VertexAttribute>& VertexBufferLayout::getAttributes() const {
        return mAttributes;
    }

    LzSizeT VertexBufferLayout::getSizeFor(const PrimitiveType& type) {
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
                LZ_ENGINE_ASSERT(false, "PRIMITIVE TYPE [NONE] IS NOT SUPPORTED");
                return 0;
            }
        }
    }

    LzSizeT VertexBufferLayout::getElementSizeFor(const PrimitiveType& type) {
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
                LZ_ENGINE_ASSERT(false, "PRIMITIVE TYPE [NONE] IS NOT SUPPORTED");
                return 0;
            }
        }
    }



    //*******************************************************
    //*                     ArrayBuffer                     *
    //*******************************************************

    ArrayBuffer::ArrayBuffer(uint32_t id, LzSizeT dataSize, LzSizeT vertexCount):
        mID(id),
        mDataSize(dataSize),
        mVertexCount(vertexCount) {

    }

    void ArrayBuffer::bind() const {
        RendererBackend::bindArrayBuffer(this);
    }

    void ArrayBuffer::setBufferLayout(const VertexBufferLayout* layout, const Shader* shader) const {
        RendererBackend::setBufferLayout(this, layout, shader);
    }



    //*******************************************************
    //*                     IndexBuffer                     *
    //*******************************************************

    IndexBuffer::IndexBuffer(uint32_t id, LzSizeT count):
    mID(id),
    mIndexCount(count) {

    }

    void IndexBuffer::bind() const {
        RendererBackend::bindIndexBuffer(this);
    }
}