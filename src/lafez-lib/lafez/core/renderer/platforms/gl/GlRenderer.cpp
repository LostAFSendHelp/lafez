#include <glad/glad.h>
#include <lafez/utils/Log.hpp>
#include <lafez/core/assets/Asset.hpp>
#include <GLFW/glfw3.h>
#include "GlRenderer.hpp"

namespace Lafez {

    GlRenderer::GlRenderer(GLFWwindow* windowPtr) :
        mWindowPtr(windowPtr) {

    }

    /********************************************************
    *                      Singleton                        *
    ********************************************************/

    void GlRenderer::initImpl() {
        LZ_ENGINE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "FAILED TO LOAD OPENGL FUNCTIONS");
        LZ_ENGINE_INFO("OPENGL version {0}", glGetString(GL_VERSION));
        LZ_ENGINE_INFO("GL WINDOW INITIALIZED");
        LZ_ENGINE_INFO("RENDERER INITIALIZED TO OPENGL");
    }

    void GlRenderer::terminateImpl() {
        LZ_ENGINE_INFO("OPENGL RENDERER TERMINATED");
    }



    /********************************************************
    *                        Generic                        *
    ********************************************************/

    void GlRenderer::clearBufferImpl(float red, float green, float blue, float alpha) {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GlRenderer::setViewportImpl(int x, int y, LzSizeT width, LzSizeT height) {
        glViewport(x, y, width, height);
    }

    void GlRenderer::swapBuffersImpl() {
        glfwSwapBuffers(mWindowPtr);
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

    void GlRenderer::deleteShaderImpl(Shader& shader) {
        LZ_ENGINE_GUARD_VOID(!shader.mIsDeleted, "Shader is already deleted");
        glDeleteProgram(shader.mID);
        shader.mIsDeleted = true;
    }

    void GlRenderer::useShaderImpl(const Shader& shader) const {
        LZ_ENGINE_GUARD_VOID(!shader.mIsDeleted, "Shader is already deleted");
        glUseProgram(shader.mID);
    }

    void GlRenderer::resetShaderImpl() const {
        glUseProgram(0);
    }

    Shader* GlRenderer::genDefaultShaderImpl() const {
        return genShader(
            "GLSL DEFAULT SHADER",
            Asset::getString("assets/shaders/glsl/vertex_shader.glsl"),
            Asset::getString("assets/shaders/glsl/fragment_shader.glsl"),
            false
        );
    }



    /********************************************************
    *                      ArrayBuffer                      *
    ********************************************************/

    ArrayBuffer* GlRenderer::genArrayBufferImpl(float* data, LzSizeT dataSize, LzSizeT vertexCount) {
        uint32_t buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return new ArrayBuffer{ buffer, dataSize, vertexCount };
    }

    bool GlRenderer::bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const {
        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer.mID);
        // TODO: handle errors here
        return true;
    }

    void GlRenderer::setBufferLayoutImpl(ArrayBuffer& arrayBuffer, const VertexBufferLayout& layout, const Shader* shader) const {
        glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer.mID);

        auto attribs = layout.getAttributes();
        for (const auto& attrib : attribs) {
            glVertexAttribPointer(attrib.mIndex,
                                  attrib.mElementSize,
                                  glTypeForPrimitiveType(attrib.mType),
                                  GL_FALSE,
                                  attrib.mStride,
                                  (void*)attrib.mOffset);
            glEnableVertexAttribArray(attrib.mIndex);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
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

    bool GlRenderer::bindIndexBufferImpl(const IndexBuffer& indexBuffer) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.mID);
        // TODO: handle errors here
        return true;
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

    VertexArrayBindType GlRenderer::bindVertexArrayImpl(const VertexArray& vertexArray) const {
        glBindVertexArray(vertexArray.mID);

        if (!vertexArray.getArrayBuffer()) {
            return LZ_VAO_BIND_TYPE_ERROR;
        } else if (!vertexArray.getIndexBuffer()) {
            return LZ_VAO_BIND_TYPE_ARRAY;
        }

        return LZ_VAO_BIND_TYPE_INDEX;
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

    void GlRenderer::vertexArrayAddArrayBufferImpl(VertexArray& vertexArray, const LzShrPtr<ArrayBuffer>& arrayBuffer) const {
        LZ_ENGINE_GUARD_VOID(arrayBuffer, "Nullptr passed as array buffer");
        resetArrayBufferImpl();
        glBindVertexArray(vertexArray.mID);
        bindArrayBuffer(*arrayBuffer);
    }

    void GlRenderer::drawVertexArrayImpl(const VertexArray& vertexArray) const {
        switch (bindVertexArrayImpl(vertexArray)) {

        case LZ_VAO_BIND_TYPE_INDEX: {
            glDrawElements(
                GL_TRIANGLES,
                vertexArray.getIndexBuffer()->mIndexCount,
                GL_UNSIGNED_INT,
                0
            );
            break;
        }

        case LZ_VAO_BIND_TYPE_ARRAY: {
            glDrawArrays(
                GL_TRIANGLES,
                0,
                vertexArray.getArrayBuffer()->mVertexCount
            );
            break;
        }

        default: {
            LZ_ENGINE_WARN("Error drawing vertex array");
            break;
        }

        }
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
        switch (type) {
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

            default: {
                LZ_ENGINE_ASSERT(false, "PRIMITIVE TYPE [NONE] IS NOT SUPPORTED");
                return 0;
            }
        }
    }
}