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
        windowPtr(windowPtr),
        modelCBuffer(0u),
        viewCBuffer(0u),
        projectionCBuffer(0u)
    {
        LZ_RUNTIME_GUARD(windowPtr, "[GFX] Illegal attempt to pass NULL as GLFW window");
        LZ_RUNTIME_GUARD(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "[GFX] FAILED TO LOAD OPENGL FUNCTIONS");
        LZ_ENGINE_INFO("OPENGL version {0}", glGetString(GL_VERSION));
        LZ_ENGINE_INFO("GL WINDOW INITIALIZED");
        LZ_ENGINE_INFO("[GFX] INITIALIZED TO OPENGL");

        LZ_GLCALL(
            glEnable(GL_DEPTH_TEST);

            glm::mat4 identity{ 1.0f };
            GLuint cBuffers[3];
            glGenBuffers(3, cBuffers);
            for (unsigned int index = 0; index < 3; ++index) {
                glBindBuffer(GL_UNIFORM_BUFFER, cBuffers[index]);
                glBufferData(
                    GL_UNIFORM_BUFFER,
                    sizeof(glm::mat4),
                    &identity,
                    GL_DYNAMIC_DRAW
                );
            }
            glBindBuffer(GL_UNIFORM_BUFFER, 0u);
            modelCBuffer = cBuffers[0];
            viewCBuffer = cBuffers[1];
            projectionCBuffer = cBuffers[2];

            glBindBufferBase(
                GL_UNIFORM_BUFFER,
                MODEL_BUFFER_INDEX,
                modelCBuffer
            );

            glBindBufferBase(
                GL_UNIFORM_BUFFER,
                VIEW_BUFFER_INDEX,
                viewCBuffer
            );

            glBindBufferBase(
                GL_UNIFORM_BUFFER,
                PROJECTION_BUFFER_INDEX,
                projectionCBuffer
            );

            auto vao = 0u;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
        );
	}

    GlGfx::~GlGfx() {
        LZ_ENGINE_INFO("[GFX] TERMINATED");
    }

    void GlGfx::clearBuffer(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

    void GlGfx::setModel(const glm::mat4& model) {
        LZ_GLCALL(
            glBindBuffer(GL_UNIFORM_BUFFER, modelCBuffer);
            glBufferSubData(
                GL_UNIFORM_BUFFER,
                0,
                sizeof(glm::mat4),
                &model
            );
            glBindBuffer(GL_UNIFORM_BUFFER, 0u);
        );
    }

    void GlGfx::setView(const glm::mat4& view) {
        LZ_GLCALL(
            glBindBuffer(GL_UNIFORM_BUFFER, viewCBuffer);
            glBufferSubData(
                GL_UNIFORM_BUFFER,
                0,
                sizeof(glm::mat4),
                &view
            );
            glBindBuffer(GL_UNIFORM_BUFFER, 0u);
        );
    }

    void GlGfx::setProjection(const glm::mat4& projection) {
        LZ_GLCALL(
            glBindBuffer(GL_UNIFORM_BUFFER, projectionCBuffer);
            glBufferSubData(
                GL_UNIFORM_BUFFER,
                0,
                sizeof(glm::mat4),
                &projection
            );
            glBindBuffer(GL_UNIFORM_BUFFER, 0u);
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