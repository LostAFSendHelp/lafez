#pragma once
#include <lafezlib_export.h>
#include <lafez/lafez_pch.hpp>

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
    *                     BufferLayout                      *
    ********************************************************/

    enum class PrimitiveType {
        None,
        Int, Vec2i, Vec3i, Vec4i,
        Float, Vec2f, Vec3f, Vec4f
    };

    struct LAFEZLIB BufferLayout {
    public:
        BufferLayout(const LzVec<PrimitiveType>& types);
        BufferLayout(LzVec<PrimitiveType>&& types);
        ~BufferLayout() = default;

        const LzVec<PrimitiveType>& getTypes() const;
        static LzSizeT getSizeFor(const PrimitiveType& type);
        
    private:
        LzVec<PrimitiveType> mTypes;
    };



    /********************************************************
    *                     ArrayBuffer                       *
    ********************************************************/

    class LAFEZLIB ArrayBuffer {
    public:
        friend class RendererBackend;
        friend class GlRenderer;
        friend class DxRenderer;
        friend class VkRenderer;

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

    /********************************************************
    *                     IndexBuffer                       *
    ********************************************************/

    class LAFEZLIB IndexBuffer {
    public:
        friend class RendererBackend;
        friend class GlRenderer;
        friend class DxRenderer;
        friend class VkRenderer;

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