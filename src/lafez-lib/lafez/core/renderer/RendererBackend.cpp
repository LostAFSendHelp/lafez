#include <lafez/utils/Log.hpp>
#include <lafez/core/renderer/Shader.hpp>
#include <lafez/core/renderer/Buffer.hpp>
#include "RendererBackend.hpp"

#define LZ_LOCAL_GUARD LZ_ENGINE_ASSERT(sShared, "ATTEMPTING TO CALL RENDERER BACKEND FUNCTIONS BEFORE STARTUP")

namespace Lafez {
    LzUniPtr<RendererBackend> RendererBackend::sShared{ nullptr };

    RendererBackend::~RendererBackend() {
        terminateImpl();
    }

    Shader* RendererBackend::genShader(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) {
        LZ_LOCAL_GUARD;

        return sShared->genShaderImpl(name, vSource, fSource, retain);
    }

    ArrayBuffer* RendererBackend::genArrayBuffer(float* data, LzSizeT size) {
        LZ_LOCAL_GUARD;

        return sShared->genArrayBufferImpl(data, size);
    }

    IndexBuffer* RendererBackend::genIndexBuffer(uint32_t* indices, LzSizeT count) {
        LZ_LOCAL_GUARD;

        return sShared->genIndexBufferImpl(indices, count);
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

    void RendererBackend::deleteShader(const Shader& shader) {
        LZ_LOCAL_GUARD;

        sShared->deleteShaderImpl(shader);
    }

    void RendererBackend::bindArrayBuffer(const ArrayBuffer& arrayBuffer) {
        LZ_LOCAL_GUARD;

        sShared->bindArrayBufferImpl(arrayBuffer);
    }

    void RendererBackend::bindIndexBuffer(const IndexBuffer& indexBuffer) {
        LZ_LOCAL_GUARD;

        sShared->bindIndexBufferImpl(indexBuffer);
    }

    void RendererBackend::resetArrayBuffer() {
        LZ_LOCAL_GUARD;

        sShared->resetArrayBufferImpl();
    }

    void RendererBackend::resetIndexBuffer() {
        LZ_LOCAL_GUARD;

        sShared->resetIndexBufferImpl();
    }
}

#undef LZ_LOCAL_GUARD