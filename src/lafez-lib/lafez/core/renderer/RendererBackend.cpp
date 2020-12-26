#include <lafez/core/renderer/Shader.hpp>
#include <lafez/core/renderer/Buffer.hpp>
#include "RendererBackend.hpp"

#define LZ_LOCAL_GUARD LZ_ENGINE_ASSERT(sShared, "ATTEMPTING TO CALL RENDERER BACKEND FUNCTIONS BEFORE STARTUP")

namespace Lafez {

    /********************************************************
    *                      Singleton                        *
    ********************************************************/

    LzUniPtr<RendererBackend> RendererBackend::sShared{ nullptr };

    void RendererBackend::shutDown() {
        if (sShared != nullptr) {
            sShared->terminateImpl();
        }

        sShared.reset();
    }

    bool RendererBackend::isInitialized() {
        return sShared != nullptr;
    }



    /********************************************************
    *                        Shader                         *
    ********************************************************/

    Shader* RendererBackend::genShader(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain) {
        LZ_LOCAL_GUARD;

        return sShared->genShaderImpl(name, vSource, fSource, retain);
    }

    void RendererBackend::deleteShader(const Shader& shader) {
        LZ_LOCAL_GUARD;

        sShared->deleteShaderImpl(shader);
    }

    void RendererBackend::useShader(const Shader& shader) {
        LZ_LOCAL_GUARD;

        sShared->useShaderImpl(shader);
    }

    void RendererBackend::resetShader() {
        LZ_LOCAL_GUARD;

        sShared->resetShaderImpl();
    }



    /********************************************************
    *                      ArrayBuffer                      *
    ********************************************************/

    ArrayBuffer* RendererBackend::genArrayBuffer(float* data, LzSizeT size) {
        LZ_LOCAL_GUARD;

        return sShared->genArrayBufferImpl(data, size);
    }

    void RendererBackend::bindArrayBuffer(const ArrayBuffer& arrayBuffer) {
        LZ_LOCAL_GUARD;

        sShared->bindArrayBufferImpl(arrayBuffer);
    }

    void RendererBackend::setBufferLayout(const ArrayBuffer& buffer, const VertexBufferLayout& layout) {
        LZ_LOCAL_GUARD;

        sShared->setBufferLayoutImpl(buffer, layout);
    }

    void RendererBackend::resetArrayBuffer() {
        LZ_LOCAL_GUARD;

        sShared->resetArrayBufferImpl();
    }



    /********************************************************
    *                      IndexBuffer                      *
    ********************************************************/

    IndexBuffer* RendererBackend::genIndexBuffer(uint32_t* indices, LzSizeT count) {
        LZ_LOCAL_GUARD;

        return sShared->genIndexBufferImpl(indices, count);
    }

    void RendererBackend::bindIndexBuffer(const IndexBuffer& indexBuffer) {
        LZ_LOCAL_GUARD;

        sShared->bindIndexBufferImpl(indexBuffer);
    }

    void RendererBackend::resetIndexBuffer() {
        LZ_LOCAL_GUARD;

        sShared->resetIndexBufferImpl();
    }



    /********************************************************
    *                      VertexArray                      *
    ********************************************************/

    VertexArray* RendererBackend::genVertexArray() {
        LZ_LOCAL_GUARD;

        return sShared->genVertexArrayImpl();
    }

    void RendererBackend::bindVertexArray(const VertexArray& vertexArray) {
        LZ_LOCAL_GUARD;

        sShared->bindVertexArrayImpl(vertexArray);
    }

    void RendererBackend::unbindVertexArray(const VertexArray& vertexArray) {
        LZ_LOCAL_GUARD;

        sShared->unbindVertexArrayImpl(vertexArray);
    }

    void RendererBackend::resetVertexArray() {
        LZ_LOCAL_GUARD;

        sShared->resetVertexArrayImpl();
    }

    void RendererBackend::renderExample(const VertexArray& vertexArray) {
        LZ_LOCAL_GUARD;

        sShared->renderExampleImpl(vertexArray);
    }
}

#undef LZ_LOCAL_GUARD