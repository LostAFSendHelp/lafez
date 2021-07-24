#include <lafez/core/renderer/RendererBackend.hpp>
#include "Shader.hpp"

namespace Lafez {
    Shader::Shader(uint32_t id, const LzString& name):
        mID(id),
        mName(name),
        mIsDeleted(false) {

    }

    void Shader::use() const {
        RendererBackend::useShader(*this);
    }
}