#include <lafez/utils/Log.hpp>
#include <lafez/core/renderer/RendererBackend.hpp>
#include "Buffer.hpp"

namespace Lafez {

    /********************************************************
    *                     VertexBufferLayout                      *
    ********************************************************/

    VertexBufferLayout::VertexBufferLayout(const LzVec<PrimitiveType>& types):
    mAttributes() {
        uint8_t iteration = 0;
        LzSizeT offset = 0;
        LzSizeT stride = 0;

        for (const auto& type : types) {
            VertexAttribute attrib{ };
            attrib.mIndex = iteration;
            attrib.mElementSize = getElementSizeFor(type);
            attrib.mOffset = stride;
            attrib.mType = type;
            mAttributes.push_back(attrib);

            stride += getSizeFor(type);
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
        switch (type)
        {
        case LZ_PTYPE_INT:      return sizeof(int32_t);
        case LZ_PTYPE_VEC2I:    return sizeof(int32_t) * 2;
        case LZ_PTYPE_VEC3I:    return sizeof(int32_t) * 3;
        case LZ_PTYPE_VEC4I:    return sizeof(int32_t) * 4;
        case LZ_PTYPE_FLOAT:    return sizeof(float);
        case LZ_PTYPE_VEC2F:    return sizeof(float) * 2;
        case LZ_PTYPE_VEC3F:    return sizeof(float) * 3;
        case LZ_PTYPE_VEC4F:    return sizeof(float) * 4;
        }

        LZ_ENGINE_ASSERT(false, "PRIMITIVE TYPE [NONE] IS NOT SUPPORTED");
        return 0;
    }

    LzSizeT VertexBufferLayout::getElementSizeFor(const PrimitiveType& type) {
        switch (type)
        {
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
        }

        LZ_ENGINE_ASSERT(false, "PRIMITIVE TYPE [NONE] IS NOT SUPPORTED");
        return 0;
    }



    //*******************************************************
    //*                     ArrayBuffer                     *
    //*******************************************************

    ArrayBuffer::ArrayBuffer(uint32_t id):
    mID(id) {

    }

    void ArrayBuffer::bind() const {
        RendererBackend::bindArrayBuffer(*this);
    }



    //*******************************************************
    //*                     IndexBuffer                     *
    //*******************************************************

    IndexBuffer::IndexBuffer(uint32_t id):
    mID(id) {

    }

    void IndexBuffer::bind() const {
        RendererBackend::bindIndexBuffer(*this);
    }
}