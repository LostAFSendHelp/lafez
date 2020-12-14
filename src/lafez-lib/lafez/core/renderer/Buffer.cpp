#include <lafez/core/renderer/RendererBackend.hpp>
#include "Buffer.hpp"

namespace Lafez {

    /********************************************************
    *                     BufferLayout                      *
    ********************************************************/

    BufferLayout::BufferLayout(const LzVec<PrimitiveType>& types):
    mTypes(types) {

    }

    BufferLayout::BufferLayout(LzVec<PrimitiveType>&& types):
    mTypes(types) {

    }

    const LzVec<PrimitiveType>& BufferLayout::getTypes() const {
        return mTypes;
    }

    LzSizeT BufferLayout::getSizeFor(const PrimitiveType& type) {
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
        
        default:                return 0;
        }
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