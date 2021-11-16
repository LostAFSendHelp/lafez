#include <lafez/platform_headers/lafez_gl.hpp>
#include <lafez/utils/Log.hpp>
#include <lafez/misc/lafez_exception.hpp>
#include <lafez/core/assets/Asset.hpp>
#include "GlGfx.hpp"
#include "GlShader.hpp"
#include "GlBuffer.hpp"

namespace Lafez {
	GlGfx::GlGfx(GLFWwindow* windowPtr) :
        Gfx(),
        windowPtr(windowPtr)
    {
        LZ_RUNTIME_GUARD(windowPtr, "[GFX] Illegal attempt to pass NULL as GLFW window");
        LZ_RUNTIME_GUARD(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "[GFX] FAILED TO LOAD OPENGL FUNCTIONS");
        LZ_ENGINE_INFO("OPENGL version {0}", glGetString(GL_VERSION));
        LZ_ENGINE_INFO("GL WINDOW INITIALIZED");
        LZ_ENGINE_INFO("[GFX] INITIALIZED TO OPENGL");

        auto vao = 0u;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
	}

    GlGfx::~GlGfx() {
        LZ_ENGINE_INFO("[GFX] TERMINATED");
    }

    void GlGfx::clearBuffer(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GlGfx::setViewport(float x, float y, float width, float height) {
        glViewport((int)x, (int)y, (int)width, (int)height);
    }

    void GlGfx::swapBuffers() {
        LZ_RUNTIME_GUARD(windowPtr, "[GFX] GLFW window must not be NULL");
        glfwSwapBuffers(windowPtr);
    }
    
    void GlGfx::drawList(unsigned int vertices) {
        LZ_GLCALL(
            glDrawArrays(GL_TRIANGLES, 0, vertices);
        );
    }

    void GlGfx::drawIndexed(unsigned int indices) {
        LZ_GLCALL(
            glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
        );
    }

    Bindable* GlGfx::genShader(
        const LzString& name,
        const LzString& vSource,
        const LzString& fSource,
        bool retain
    ) {
        return new GlShader {
            name,
            vSource,
            fSource
        };
    }

    Bindable* GlGfx::genVertexBuffer(
        float* data,
        LzSizeT dataSize,
        LzSizeT vertexCount
    ) {
        return new GlVBuffer {
            data,
            dataSize,
            vertexCount
        };
    }

    Bindable* GlGfx::genIndexBuffer(
        uint32_t* indices,
        LzSizeT indexCount
    ) {
        return new GlIBuffer {
            indices,
            indexCount
        };
    }

    Bindable* GlGfx::genVBLayout(
        VertexAttribute* attributes,
        LzSizeT attribCount,
        const Bindable* shader
    ) {
        return new GlBufferLayout {
            attributes,
            attribCount
        };
    }

    Bindable* GlGfx::genDefaultShader() {
        return genShader(
            "GLSL DEFAULT SHADER",
            Asset::getString("assets/shaders/glsl/vertex_shader.glsl"),
            Asset::getString("assets/shaders/glsl/fragment_shader.glsl"),
            false
        );
    }
}