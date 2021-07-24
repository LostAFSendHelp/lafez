#include <lafez/core/renderer/RendererBackend.hpp>
#include "VertexArray.hpp"

namespace Lafez {
    VertexArray::VertexArray(uint32_t id):
    mID(id),
    mArrayBuffer(nullptr),
    mIndexBuffer(nullptr) {

    }

    VertexArray::~VertexArray() {

    }

    void VertexArray::bind() const {
        RendererBackend::bindVertexArray(*this);
    }

    void VertexArray::unbind() const {
        RendererBackend::unbindVertexArray(*this);
    }

    void VertexArray::addArrayBuffer(const LzShrPtr<ArrayBuffer>& arrayBuffer) {
        RendererBackend::vertexArrayAddArrayBuffer(*this, arrayBuffer);
        mArrayBuffer = arrayBuffer;
    }

    void VertexArray::addIndexBuffer(const LzShrPtr<IndexBuffer>& indexBuffer) {
        RendererBackend::bindVertexArray(*this);
        RendererBackend::resetIndexBuffer();

        indexBuffer->bind();
        mIndexBuffer = indexBuffer;
    }

    const LzShrPtr<ArrayBuffer>& VertexArray::getArrayBuffer() const {
        return mArrayBuffer;
    }

    const LzShrPtr<IndexBuffer>& VertexArray::getIndexBuffer() const {
        return mIndexBuffer;
    }
}