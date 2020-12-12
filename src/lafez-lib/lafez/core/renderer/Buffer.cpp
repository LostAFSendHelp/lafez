#include <lafez/core/renderer/RendererBackend.hpp>
#include "Buffer.hpp"

namespace Lafez {

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