#pragma once
#include <lafezlib_export.h>
#include <lafez/lafez_pch.hpp>
#include "Shader.hpp"

#define LZ_PTYPE_NONE       ::Lafez::PrimitiveType::None
#define LZ_PTYPE_INT        ::Lafez::PrimitiveType::Int
#define LZ_PTYPE_VEC2I      ::Lafez::PrimitiveType::Vec2i
#define LZ_PTYPE_VEC3I      ::Lafez::PrimitiveType::Vec3i
#define LZ_PTYPE_VEC4I      ::Lafez::PrimitiveType::Vec4i
#define LZ_PTYPE_FLOAT      ::Lafez::PrimitiveType::Float
#define LZ_PTYPE_VEC2F      ::Lafez::PrimitiveType::Vec2f
#define LZ_PTYPE_VEC3F      ::Lafez::PrimitiveType::Vec3f
#define LZ_PTYPE_VEC4F      ::Lafez::PrimitiveType::Vec4f

namespace Lafez {

    /********************************************************
    *                  VertexBufferLayout                   *
    ********************************************************/

    enum class PrimitiveType {
        None,
        Int, Vec2i, Vec3i, Vec4i,
        Float, Vec2f, Vec3f, Vec4f
    };

    struct LAFEZLIB VertexAttribute {
    public:
        uint32_t mIndex;
        LzSizeT mSize;
        LzSizeT mElementSize;
        LzSizeT mStride;
        LzSizeT mOffset;
        PrimitiveType mType;

        VertexAttribute(const LzString& name, PrimitiveType type);
        VertexAttribute(const VertexAttribute& other);
        VertexAttribute(VertexAttribute&& other) = default;
        ~VertexAttribute() = default;

        VertexAttribute& operator=(const VertexAttribute& other);
        const LzString& getName() const;
    private:
        LzString mName;
    };

    struct LAFEZLIB VertexBufferLayout {
    public:
        VertexBufferLayout(const LzVec<VertexAttribute>& types);
        ~VertexBufferLayout() = default;

        const LzVec<VertexAttribute>& getAttributes() const;
        static LzSizeT getSizeFor(const PrimitiveType& type);
        static LzSizeT getElementSizeFor(const PrimitiveType& type);

    private:
        LzVec<VertexAttribute> mAttributes;
    };



    /********************************************************
    *                     ArrayBuffer                       *
    ********************************************************/

    class LAFEZLIB ArrayBuffer {
    public:

        /// The renderer ID of the array buffer
        const uint32_t mID;
        /// The size in bytes of the array buffer data
        const LzSizeT mDataSize;
        /// The vertex count of the array buffer, used for non-indexed draw calls
        const LzSizeT mVertexCount;



        /**
         * @brief Construct a new Array Buffer object. Only for testing purposes should this constructor be called directly by client. For actual use, prefer RendererBackend::genArrayBuffer(...) instead
         * 
         * @param id The renderer ID of the array buffer
         */
        ArrayBuffer(uint32_t id, LzSizeT dataSize, LzSizeT vertexCount);



        /**
         * @brief Destroy the Array Buffer object
         */
        ~ArrayBuffer() = default;



        /**
         * @brief Bind the array buffer for rendering, equivalent to calling RendererBackend::bindArrayBuffer(*this)
         */
        void bind() const;



        /**
         * @brief Set the Buffer Layout for the ArrayBuffer.
         * Only changes data in the backend, does not retain any data on the array buffer itself.
         * Equivalent to calling RendererBackend::setBufferLayout(*this, layout, shader)
         * 
         * @param layout The buffer layout to apply to the array buffer
         * @param shader The shader to validate the layout against, can be `nullptr` if backend is GL
         */
        void setBufferLayout(const VertexBufferLayout* layout, const Shader* shader) const;

    private:

    };

    /********************************************************
    *                     IndexBuffer                       *
    ********************************************************/

    class LAFEZLIB IndexBuffer {
    public:

        /// The renderer ID of the index buffer
        const uint32_t mID;
        /// The index count of the index buffer
        const LzSizeT mIndexCount;



        /**
         * @brief Construct a new Index Buffer object. Only for testing purposes should this constructor be called directly by client. For actual use, prefer RendererBackend::genIndexBuffer(...) instead
         * 
         * @param id The renderer ID of the index buffer
         */
        IndexBuffer(uint32_t id, LzSizeT count);



        /**
         * @brief Destroy the Index Buffer object
         */
        ~IndexBuffer() = default;



        /**
         * @brief Bind the index buffer for rendering, equivalent to calling RendererBackend::bindIndexBuffer(*this)
         */
        void bind() const;

    private:

    };
};