#pragma once
#include <lafez/lafez_pch.hpp>
#include <lafez/core/renderer/Buffer.hpp>

namespace Lafez {
    class VertexArray {
    public:

        /// The renderer ID of the Vertex Array
        const uint32_t mID;

        /**
         * @brief Construct a new Vertex Array object, keeping a handle to all currently bound buffer states. Only for testing purposes should the constructor be called directly by client. For actual use prefer RendererBackend::genVertexArray(...) instead
         * 
         * @param id The renderer ID of the Vertex Array object
         */
        VertexArray(uint32_t id);



        /**
         * @brief Destroy the Vertex Array object
         */
        ~VertexArray();



        /**
         * @brief Bind the Vertex Array object, thereby binding all child buffers. Equivalent to calling RendererBackend::bindVertexArray(*this)
         */
        void bind() const;



        /**
         * @brief Unbind the Vertex Array object, there by unbinding all child buffers. Equivalent to calling RendererBackend::unbindVertexArray(*this)
         */
        void unbind() const;



        /**
         * @brief Add an array buffer to the Vertex Array object. The renderer will only allow the binding of only 1 array buffer (new one overwrites old), so make sure to use interleaved buffers for VAOs. Will bind this vertex array object before adding array buffer
         * 
         * @param arrayBuffer the array buffer to be bound
         */
        void addArrayBuffer(const LzShrPtr<ArrayBuffer>& arrayBuffer);



        /**
         * @brief Add an index buffer to the Vertex Array object. Only accepts 1 index buffer, the new one overwrites the old
         * 
         * @param indexBuffer 
         */
        void addIndexBuffer(const LzShrPtr<IndexBuffer>& indexBuffer);



        /**
         * @brief Get the Array Buffer object
         * 
         * @return const LzShrPtr<ArrayBuffer>& 
         */
        const LzShrPtr<ArrayBuffer>& getArrayBuffer() const;



        /**
         * @brief Get the Index Buffer object
         * 
         * @return const LzShrPtr<IndexBuffer>& 
         */
        const LzShrPtr<IndexBuffer>& getIndexBuffer() const;

    private:
        LzShrPtr<ArrayBuffer> mArrayBuffer;
        LzShrPtr<IndexBuffer> mIndexBuffer;

    };
};