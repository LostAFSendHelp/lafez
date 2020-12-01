#include <lafez/utils/Log.hpp>
#include "Input.hpp"

namespace Lafez {
    LzUniPtr<Input> Input::sShared{ nullptr };

    void Input::shutDown() {
        if (sShared) {
            sShared->terminateImpl();
        }

        sShared.reset();
    }

    bool Input::getKey(int keycode) {
        LZ_ENGINE_GUARD_VAL(sShared, false, "ATTEMPT TO GETKEY FROM UNINITIALIZED INPUT, DEFAULTING TO FALSE");

        return sShared->getKeyImpl(keycode);
    }

    LzPair<float, float> Input::getMousePosition() {
        LZ_ENGINE_GUARD_VAL(sShared, (LzPair<float, float>{ .0f, .0f }), "ATTEMPT TO GETKEY FROM UNINITIALIZED INPUT, DEFAULTING TO { 0, 0 }");

        return sShared->getMousePositionImpl();
    }

    bool Input::isInitialized() {
        return sShared != nullptr;
    }
};