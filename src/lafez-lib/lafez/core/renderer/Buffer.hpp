#pragma once
#include <lafez/lafez_pch.hpp>

namespace Lafez {

    //*******************************************************
    //*                     ArrayBuffer                     *
    //*******************************************************

    class ArrayBuffer {
    public:
        friend class RendererBackend;

        /// The renderer ID of the array buffer
        const uint32_t mID;



        /**
         * @brief Destroy the Array Buffer object
         */
        ~ArrayBuffer() = default;



        /**
         * @brief Bind the array buffer for rendering, equivalent to calling RendererBackend::bindArrayBuffer(*this)
         */
        void bind() const;

    private:

        /**
         * @brief Construct a new Array Buffer object
         * 
         * @param id The renderer ID of the array buffer
         */
        ArrayBuffer(uint32_t id);

    };

    //*******************************************************
    //*                     Indexbuffer                     *
    //*******************************************************

    class IndexBuffer {
    public:
        friend class RendererBackend;

        /// The renderer ID of the index buffer
        const uint32_t mID;



        /**
         * @brief Destroy the Index Buffer object
         */
        ~IndexBuffer() = default;



        /**
         * @brief Bind the index buffer for rendering, equivalent to calling RendererBackend::bindIndexBuffer(*this)
         */
        void bind() const;

    private:

        /**
         * @brief Construct a new Index Buffer object
         * 
         * @param id The renderer ID of the index buffer
         */
        IndexBuffer(uint32_t id);

    };
};