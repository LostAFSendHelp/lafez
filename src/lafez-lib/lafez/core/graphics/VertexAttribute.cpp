#include "VertexAttribute.hpp"

namespace Lafez {
    VertexAttribute::VertexAttribute(
        const LzString& name,
        PrimitiveType type
    ) :
        name(name),
        type(type)
    {

    }

    VertexAttribute::VertexAttribute(const VertexAttribute& other) :
        name(other.name),
        type(other.type)
    {

    }

    VertexAttribute::VertexAttribute(VertexAttribute&& other) :
        name(std::move(other.name)),
        type(other.type)
    {

    }
}