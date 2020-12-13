#include <glad/glad.h>
#include <lafez/utils/Log.hpp>
#include "GlRenderer.hpp"

namespace Lafez {
    Shader* GlRenderer::genShaderImpl(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain) {
        auto vertex = createShader(GL_VERTEX_SHADER, vSource);
        auto fragment = createShader(GL_FRAGMENT_SHADER, fSource);
        
        auto program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);

        int status;
        int length;
        char* log = nullptr;
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        if (!status) {
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            log = new char[length];
            glGetProgramInfoLog(program, length * sizeof(char), NULL, log);
            LZ_ENGINE_WARN("PROGRAM LINK ERROR: {0}", log);
            delete[] log;
        }

        return new Shader{ program, name };
    }

    ArrayBuffer* GlRenderer::genArrayBufferImpl(float* data, LzSizeT size) {
        return nullptr;
    }

    IndexBuffer* GlRenderer::genIndexBufferImpl(uint32_t* indices, LzSizeT count) {
        return nullptr;
    }

    void GlRenderer::deleteShaderImpl(const Shader& shader) const {

    }

    void GlRenderer::useShaderImpl(const Shader& shader) const {

    }

    void GlRenderer::resetShaderImpl() const {

    }

    void GlRenderer::bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const {

    }

    void GlRenderer::bindIndexBufferImpl(const IndexBuffer& indexBuffer) const {

    }

    void GlRenderer::resetArrayBufferImpl() const {

    }

    void GlRenderer::resetIndexBufferImpl() const {

    }

    void GlRenderer::initImpl() {

    }

    void GlRenderer::terminateImpl() {

    }

    uint32_t GlRenderer::createShader(uint32_t type, const LzString& source) const {
        auto shader = glCreateShader(type);
        auto shaderSource = source.c_str();
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        int status;
        int length;
        char* log = nullptr;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (!status) {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            log = new char[length];
            glGetShaderInfoLog(shader, length * sizeof(char), NULL, log);
            LZ_ENGINE_WARN("SHADER COMPILATION ERROR {0}", log);
            delete[] log;
        }

        return shader;
    }
}