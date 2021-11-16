#pragma once
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>

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
    enum class PrimitiveType {
        None,
        Int, Vec2i, Vec3i, Vec4i,
        Float, Vec2f, Vec3f, Vec4f
    };

    struct LAFEZLIB VertexAttribute {
    public:
        LzString name;
        PrimitiveType type;

        VertexAttribute(const LzString& name, PrimitiveType type);
        VertexAttribute(const VertexAttribute& other);
        VertexAttribute(VertexAttribute&& other);
        ~VertexAttribute() = default;

        VertexAttribute& operator = (const VertexAttribute& other) = delete;
        VertexAttribute& operator = (VertexAttribute&& other) = delete;

    private:
    };
};