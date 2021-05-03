#pragma once
#include <lafez/lafez_pch.hpp>
#include <lafez/utils/Log.hpp>
#include <lafez/core/renderer/Shader.hpp>
#include <lafez/core/renderer/Buffer.hpp>
#include <lafez/core/renderer/VertexArray.hpp>

namespace Lafez {

    class LAFEZLIB RendererBackend {
    public:
        
        /**
         * @brief Destroy the Renderer Backend object
         */
        virtual ~RendererBackend() = default;



        /********************************************************
        *                      Singleton                        *
        ********************************************************/
        
        /**
         * @brief Initialize the renderer backend singleton
         * 
         * @tparam T RendererBackend derived
         * @tparam Args deduced
         * @param args Constructor args of T
         */
        template<typename T, typename ... Args>
        static void startUp(Args&& ... args);



        /**
         * @brief Terminate the renderer backend singleton 
         */
        static void shutDown();



        /**
         * @brief Whether the Renderer backend singleton has been initialized
         * 
         * @return true If it has
         * @return false Otherwise
         */
        static bool isInitialized();



        /********************************************************
        *                        Generic                        *
        ********************************************************/

        /**
         * @brief Clear the back buffer with specified color
         * @param red component of the RGBA code
         * @param green component of the RGBA code
         * @param blue component of the RGBA code
         * @param alpha component of the RGBA code
         */
        static void clearBuffer(float red, float green, float blue, float alpha);



        /**
         * @brief Set viewport for render area
         * @param x horizontal origin, left to right
         * @param y vertical origin, top down
         * @param width width of the viewport
         * @param height height of the viewport
         */
        static void setViewport(int x, int y, LzSizeT width, LzSizeT height);



        /********************************************************
        *                        Shader                         *
        ********************************************************/

        /**
         * @brief Create a Shader program
         * 
         * @param name The name of the Shader to be created
         * @param vSource The source code of the Vertex shader
         * @param fSource The source code of the Fragment shader
         * @param retain Discard the child shaders after linking
         * @return Shader*
         */
        static Shader* genShader(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false);



        /**
         * @brief Delete a shader object
         * 
         * @param shader The shader to be deleted
         */
        static void deleteShader(const Shader& shader);



        /**
         * @brief Use a shader to use for subsequent object renderings
         * 
         * @param shader The shader to use
         */
        static void useShader(const Shader& shader);



        /**
         * @brief Bind the current Shader to 0
         */
        static void resetShader();



        /********************************************************
        *                      ArrayBuffer                      *
        ********************************************************/

        /**
         * @brief Create an array buffer object
         * 
         * @param data The buffer data
         * @param dataSize The size of buffer data
         * @param vertexCount The number of vertices that the buffer contains
         * @return ArrayBuffer*
         */
        static ArrayBuffer* genArrayBuffer(float* data, LzSizeT dataSize, LzSizeT vertexCount);



        /**
         * @brief Bind an ArrayBuffer object for rendering
         * 
         * @param arrayBuffer The array buffer to bind
         */
        static void bindArrayBuffer(const ArrayBuffer& arrayBuffer);



        /**
         * @brief Apply a buffer layout to an array buffer
         * 
         * @param arrayBuffer The buffer to which to apply the layout
         * @param layout The layout to apply to the array buffer
         */
        static void setBufferLayout(const ArrayBuffer& arrayBuffer, const VertexBufferLayout& layout);



        /**
         * @brief Bind array buffer to 0
         */
        static void resetArrayBuffer();



        /********************************************************
        *                      IndexBuffer                      *
        ********************************************************/

        /**
         * @brief Create an array buffer object
         * 
         * @param indices The buffer indices
         * @param indexCount The number of indices
         * @return ArrayBuffer*
         */
        static IndexBuffer* genIndexBuffer(uint32_t* indices, LzSizeT indexCount);



        /**
         * @brief Bind an IndexBuffer object for rendering
         * 
         * @param indexBuffer The index buffer to bind
         */
        static void bindIndexBuffer(const IndexBuffer& indexBuffer);



        /**
         * @brief Bind index buffer to 0
         */
        static void resetIndexBuffer();



        /********************************************************
        *                      VertexArray                      *
        ********************************************************/

        /**
         * @brief Create a Vertex Array object
         * 
         * @return VertexArray* 
         */
        static VertexArray* genVertexArray();



        /**
         * @brief Bind a vertex array object for renderering
         * 
         * @param vertexArray the vertex array to be bound
         */
        static void bindVertexArray(const VertexArray& vertexArray);



        /**
         * @brief Unbind a vertex array object
         * 
         * @param vertexArray the vertex array object to be unbound
         */
        static void unbindVertexArray(const VertexArray& vertexArray);



        /**
         * @brief Unbind the currently bound vertex array object
         */
        static void resetVertexArray();



        /**
         * @brief Draw using states bound by the vertex array object. Abort if array buffer data unavailable. Draw array if no indices found, draw indexed otherwise. The vertex array object is only bound if the state it holds has array buffer data
         * 
         * @param vertexArray The vertex array object to be bound and with whose data the renderer to draw from
         */
        static void drawVertexArray(const VertexArray& vertexArray);

    protected:
        RendererBackend() = default;

        // Generic
        virtual void clearBufferImpl(float red, float green, float blue, float alpha) = 0;
        virtual void setViewportImpl(int x, int y, LzSizeT width, LzSizeT height) = 0;

        // Shader
        virtual Shader* genShaderImpl(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) = 0;
        virtual void deleteShaderImpl(const Shader& shader) const = 0;
        virtual void useShaderImpl(const Shader& shader) const = 0;
        virtual void resetShaderImpl() const = 0;

        // ArrayBuffer
        virtual ArrayBuffer* genArrayBufferImpl(float* data, LzSizeT dataSize, LzSizeT vertexCount) = 0;
        virtual void bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const = 0;
        virtual void setBufferLayoutImpl(const ArrayBuffer& arrayBuffer, const VertexBufferLayout& layout) const = 0;
        virtual void resetArrayBufferImpl() const = 0;

        // IndexBuffer
        virtual IndexBuffer* genIndexBufferImpl(uint32_t* indices, LzSizeT indexCount) = 0;
        virtual void bindIndexBufferImpl(const IndexBuffer& indexBuffer) const = 0;
        virtual void resetIndexBufferImpl() const = 0;

        // VertexArray
        virtual VertexArray* genVertexArrayImpl() = 0;
        virtual void bindVertexArrayImpl(const VertexArray& vertexArray) const = 0;
        virtual void unbindVertexArrayImpl(const VertexArray& vertexArray) const = 0;
        virtual void resetVertexArrayImpl() const = 0;
        virtual void drawVertexArrayImpl(const VertexArray& vertexArray) const = 0;

        virtual void initImpl() = 0;
        virtual void terminateImpl() = 0;

    private:
        static LzUniPtr<RendererBackend> sShared;
    };



    template<typename T, typename ... Args>
    void RendererBackend::startUp(Args&& ... args) {
        LZ_ENGINE_GUARD_VOID((sShared == nullptr), "ATTEMPT TO RE-STARTUP NON-NULL RENDERER BACKEND INSTANCE, ABORTING...");

        RendererBackend::sShared = std::make_unique<T>(std::forward<Args>(args)...);
        RendererBackend::sShared->initImpl();
    }
};