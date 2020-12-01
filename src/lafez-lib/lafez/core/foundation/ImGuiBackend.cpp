#include <lafez/utils/Log.hpp>
#include "ImGuiBackend.hpp"

#define LZ_LOCAL_GUARD LZ_ENGINE_ASSERT(sShared, "ATTEMPTING TO CALL IMGUIBACKEND BEFORE STARTUP IS CALLED");

namespace Lafez {
    LzUniPtr<ImGuiBackend> ImGuiBackend::sShared{ nullptr };

    void ImGuiBackend::init() {
        LZ_LOCAL_GUARD;
        sShared->initImpl();
    }

    void ImGuiBackend::terminate() {
        LZ_LOCAL_GUARD;
        sShared->terminateImpl();
    }

    void ImGuiBackend::newFrame() {
        LZ_LOCAL_GUARD;
        sShared->newFrameImpl();
    }

    void ImGuiBackend::renderDrawData(ImDrawData* data) {
        LZ_LOCAL_GUARD;
        sShared->renderDrawDataImpl(data);
    }

    void ImGuiBackend::shutDown() {
        if (sShared != nullptr) {
            sShared->terminateImpl();
        }

        sShared.reset();
    }

    bool ImGuiBackend::isInitialized() {
        return sShared != nullptr;
    }
}

#undef LZ_LOCAL_GUARD
