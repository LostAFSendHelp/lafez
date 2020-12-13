#pragma once
#include <lafez/lafez_pch.hpp>

namespace Lafez {

    // Forward declaration
    class Shader;
    class ArrayBuffer;
    class IndexBuffer;

    class RendererBackend {
    public:
        
        /**
         * @brief Destroy the Renderer Backend object
         */
        virtual ~RendererBackend();
        
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
         * @brief Create an array buffer object
         * 
         * @param data The buffer data
         * @param size The size of the buffer in byte
         * @return ArrayBuffer*
         */
        static ArrayBuffer* genArrayBuffer(float* data, LzSizeT size);



        /**
         * @brief Create an array buffer object
         * 
         * @param indices The buffer indices
         * @param count The number of indices
         * @return ArrayBuffer*
         */
        static IndexBuffer* genIndexBuffer(uint32_t* indices, LzSizeT count);



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



        /**
         * @brief Bind an ArrayBuffer object for rendering
         * 
         * @param arrayBuffer The array buffer to bind
         */
        static void bindArrayBuffer(const ArrayBuffer& arrayBuffer);



        /**
         * @brief Bind an IndexBuffer object for rendering
         * 
         * @param indexBuffer The index buffer to bind
         */
        static void bindIndexBuffer(const IndexBuffer& indexBuffer);



        /**
         * @brief Bind array buffer to 0
         */
        static void resetArrayBuffer();



        /**
         * @brief Bind index buffer to 0
         */
        static void resetIndexBuffer();

    protected:
        RendererBackend() = default;

        virtual Shader* genShaderImpl(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) = 0;
        virtual ArrayBuffer* genArrayBufferImpl(float* data, LzSizeT size) = 0;
        virtual IndexBuffer* genIndexBufferImpl(uint32_t* indices, LzSizeT count) = 0;
        virtual void deleteShaderImpl(const Shader& shader) const = 0;
        virtual void useShaderImpl(const Shader& shader) const = 0;
        virtual void resetShaderImpl() const = 0;
        virtual void bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const = 0;
        virtual void bindIndexBufferImpl(const IndexBuffer& indexBuffer) const = 0;
        virtual void resetArrayBufferImpl() const = 0;
        virtual void resetIndexBufferImpl() const = 0;
        virtual void initImpl() = 0;
        virtual void terminateImpl() = 0;

    private:
        static LzUniPtr<RendererBackend> sShared;
    };



    template<typename T, typename ... Args>
    static void RendererBackend::startUp(Args&& ... args) {
        LZ_ENGINE_GUARD_VOID((sShared == nullptr), "ATTEMPT TO RE-STARTUP NON-NULL RENDERER BACKEND INSTANCE, ABORTING...");

        RendererBackend::sShared == std::make_shared<T>(std::forward<Args>(args)...);
        RendererBackend::sShared->initImpl();
    }
};