#include <lafez/core/renderer/Shader.hpp>
#include <lafez/core/renderer/Buffer.hpp>
#include "RendererBackend.hpp"

#define LZ_LOCAL_GUARD LZ_ENGINE_GUARD_THROW(sShared, "ATTEMPTING TO CALL RENDERER BACKEND FUNCTIONS BEFORE STARTUP")
#define LZ_CALL_SINGLETON(x) { LZ_LOCAL_GUARD; sShared->x; }
#define LZ_CALL_SINGLETON_RETURN(x) { LZ_LOCAL_GUARD; return sShared->x; }

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

    void RendererBackend::clearBuffer(float red, float green, float blue, float alpha) {
        LZ_CALL_SINGLETON(clearBufferImpl(red, green, blue, alpha));
    }

    void RendererBackend::setViewport(int x, int y, LzSizeT width, LzSizeT height) {
        LZ_CALL_SINGLETON(setViewportImpl(x, y, width, height));
    }

    void RendererBackend::swapBuffers() {
        LZ_CALL_SINGLETON(swapBuffersImpl());
    }



    /********************************************************
    *                        Shader                         *
    ********************************************************/

    Shader* RendererBackend::genShader(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain) {
        LZ_CALL_SINGLETON_RETURN(genShaderImpl(name, vSource, fSource, retain));
    }

    void RendererBackend::deleteShader(Shader* shader) {
        LZ_CALL_SINGLETON(deleteShaderImpl(shader));
    }

    void RendererBackend::useShader(const Shader* shader) {
        LZ_CALL_SINGLETON(useShaderImpl(shader));
    }

    void RendererBackend::resetShader() {
        LZ_CALL_SINGLETON(resetShaderImpl());
    }

    Shader* RendererBackend::genDefaultShader() {
        LZ_CALL_SINGLETON_RETURN(genDefaultShaderImpl());
    }



    /********************************************************
    *                      ArrayBuffer                      *
    ********************************************************/

    ArrayBuffer* RendererBackend::genArrayBuffer(float* data, LzSizeT dataSize, LzSizeT vertexCount) {
        LZ_CALL_SINGLETON_RETURN(genArrayBufferImpl(data, dataSize, vertexCount));
    }

    void RendererBackend::bindArrayBuffer(const ArrayBuffer* arrayBuffer) {
        LZ_CALL_SINGLETON(bindArrayBufferImpl(arrayBuffer));
    }

    void RendererBackend::setBufferLayout(const ArrayBuffer* arrayBuffer, const VertexBufferLayout* layout, const Shader* shader) {
        LZ_CALL_SINGLETON(setBufferLayoutImpl(arrayBuffer, layout, shader));
    }

    void RendererBackend::resetArrayBuffer() {
        LZ_CALL_SINGLETON(resetArrayBufferImpl());
    }



    /********************************************************
    *                      IndexBuffer                      *
    ********************************************************/

    IndexBuffer* RendererBackend::genIndexBuffer(uint32_t* indices, LzSizeT indexCount) {
        LZ_CALL_SINGLETON_RETURN(genIndexBufferImpl(indices, indexCount));
    }

    void RendererBackend::bindIndexBuffer(const IndexBuffer* indexBuffer) {
        LZ_CALL_SINGLETON(bindIndexBufferImpl(indexBuffer));
    }

    void RendererBackend::resetIndexBuffer() {
        LZ_CALL_SINGLETON(resetIndexBufferImpl());
    }



    /********************************************************
    *                      VertexArray                      *
    ********************************************************/

    VertexArray* RendererBackend::genVertexArray() {
        LZ_CALL_SINGLETON_RETURN(genVertexArrayImpl());
    }

    void RendererBackend::bindVertexArray(const VertexArray* vertexArray) {
        LZ_CALL_SINGLETON(bindVertexArrayImpl(vertexArray));
    }

    void RendererBackend::unbindVertexArray(const VertexArray* vertexArray) {
        LZ_CALL_SINGLETON(unbindVertexArrayImpl(vertexArray));
    }

    void RendererBackend::resetVertexArray() {
        LZ_CALL_SINGLETON(resetVertexArrayImpl());
    }

    void RendererBackend::drawVertexArray(const VertexArray* vertexArray) {
        LZ_CALL_SINGLETON(drawVertexArrayImpl(vertexArray));
    }
}

#undef LZ_LOCAL_GUARD
#undef LZ_CALL_SINGLETON