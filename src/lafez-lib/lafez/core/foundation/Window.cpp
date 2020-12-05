#include <lafez/utils/Log.hpp>
#include "Window.hpp"

namespace Lafez {
    LzUniPtr<Window> Window::sShared{ nullptr };

    uint16_t Window::getWidth() {
        LZ_ENGINE_GUARD_VAL(sShared, 0, "ATTEMPT TO GETWIDTH FROM UNITIALIZED WINDOW, DEFAULTING TO 0");

        return sShared->getWidthImpl();
    }

    uint16_t Window::getHeight() {
        LZ_ENGINE_GUARD_VAL(sShared, 0, "ATTEMPT TO GETHEIGHT FROM UNITIALIZED WINDOW, DEFAULTING TO 0");

        return sShared->getHeightImpl();
    }

    const LzString& Window::getName() {
        LZ_ENGINE_ASSERT(sShared, "ATTEMPTING TO GETNAME FROM UNITIALIZED WINDOW");

        return sShared->getNameImpl();
    }

    bool Window::shouldClose() {
        LZ_ENGINE_GUARD_VAL(sShared, true, "ATTEMPT TO GET SHOULDCLOSE FROM UNITIALIZED WINDOW, DEFAULTING TO TRUE");

        return sShared->shouldCloseImpl();
    }

    void Window::update() {
        LZ_ENGINE_GUARD_VOID(sShared, "ATTEMPT TO UPDATE UNINITIALIZED WINDOW, ABORTING...");

        sShared->updateImpl();
    }

    void Window::close() {
        LZ_ENGINE_GUARD_VOID(sShared, "ATTEMPT TO CLOSE UNINITIALIZED WINDOW, ABORTING...");

        sShared->closeImpl();
    }

    void* Window::getWindowPointer() {
        LZ_ENGINE_GUARD_VAL(sShared, nullptr, "ATTEMPT TO GETWINDOWPOINTER FROM UNINITIALIZED WINDOW, DEFAULTING TO NULLPTR");

        return sShared->getWindowPointerImpl();
    }

    void Window::shutDown() {
        if (sShared != nullptr) {
            sShared->terminateImpl();
            sShared.reset();
        }
    }

    bool Window::isInitialized() {
        return sShared != nullptr;
    }
}