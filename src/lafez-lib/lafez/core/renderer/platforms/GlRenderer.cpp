#include <glad/glad.h>
#include <lafez/utils/Log.hpp>
#include "GlRenderer.hpp"

namespace Lafez {

    /********************************************************
    *                      Singleton                        *
    ********************************************************/

    void GlRenderer::initImpl() {
        LZ_ENGINE_INFO("RENDERER INITIALIZED TO OPENGL");
    }

    void GlRenderer::terminateImpl() {
        LZ_ENGINE_INFO("OPENGL RENDERER TERMINATED");
    }



    /********************************************************
    *                        Shader                         *
    ********************************************************/

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

        if (retain) {
            glDetachShader(program, vertex);
            glDetachShader(program, fragment);
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        return new Shader{ program, name };
    }

    void GlRenderer::deleteShaderImpl(const Shader& shader) const {
        glDeleteProgram(shader.mID);
    }

    void GlRenderer::useShaderImpl(const Shader& shader) const {
        glUseProgram(shader.mID);
    }

    void GlRenderer::resetShaderImpl() const {
        glUseProgram(0);
    }



    /********************************************************
    *                      ArrayBuffer                      *
    ********************************************************/

    ArrayBuffer* GlRenderer::genArrayBufferImpl(float* data, LzSizeT size) {
        uint32_t buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return new ArrayBuffer{ buffer };
    }

    void GlRenderer::bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const {
        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer.mID);
    }

    void GlRenderer::setBufferLayoutImpl(const ArrayBuffer& buffer, const VertexBufferLayout& layout) const {
        bindArrayBufferImpl(buffer);

        auto attribs = layout.getAttributes();
        for(const auto& attrib : attribs) {
            glVertexAttribPointer(attrib.mIndex,
                                  attrib.mElementSize,
                                  glTypeForPrimitiveType(attrib.mType),
                                  GL_FALSE,
                                  attrib.mStride,
                                  (void*)attrib.mOffset);
            glEnableVertexAttribArray(attrib.mIndex);
        }
    }

    void GlRenderer::resetArrayBufferImpl() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }



    /********************************************************
    *                      ArrayBuffer                      *
    ********************************************************/

    IndexBuffer* GlRenderer::genIndexBufferImpl(uint32_t* indices, LzSizeT count) {
        uint32_t buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return new IndexBuffer{ buffer, count };
    }

    void GlRenderer::bindIndexBufferImpl(const IndexBuffer& indexBuffer) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.mID);
    }

    void GlRenderer::resetIndexBufferImpl() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }



    /********************************************************
    *                      VertexArray                      *
    ********************************************************/

    VertexArray* GlRenderer::genVertexArrayImpl() {
        uint32_t id = 0;
        glGenVertexArrays(1, &id);
        return new VertexArray(id);
    }

    void GlRenderer::bindVertexArrayImpl(const VertexArray& vertexArray) const {
        glBindVertexArray(vertexArray.mID);
    }

    void GlRenderer::unbindVertexArrayImpl(const VertexArray& vertexArray) const {
        int id = 0;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &id);

        if (vertexArray.mID == id) {
            glBindVertexArray(0);
        }
    }

    void GlRenderer::resetVertexArrayImpl() const {
        glBindVertexArray(0);
    }



    /********************************************************
    *                        Private                        *
    ********************************************************/

    uint32_t GlRenderer::createShader(uint32_t type, const LzString& source) {
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

    uint32_t GlRenderer::glTypeForPrimitiveType(const PrimitiveType& type) {
        switch (type)
        {
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
        }

        LZ_ENGINE_ASSERT(false, "PRIMITIVE TYPE [NONE] IS NOT SUPPORTED");
        return 0;
    }

    void GlRenderer::renderExampleImpl(const VertexArray& vertexArray) const {
        vertexArray.bind();
        glDrawElements(GL_TRIANGLES, vertexArray.getIndexBuffer()->mIndexCount, GL_UNSIGNED_INT, 0);
    }
}