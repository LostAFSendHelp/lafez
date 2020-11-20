#include "WindowResizeEvent.hpp"

namespace Lafez {
    WindowResizeEvent::WindowResizeEvent(int width, int height):
    Event(LZT_WINDOW_RESIZE),
    mWidth(width),
    mHeight(height) {

    }

    WindowResizeEvent::~WindowResizeEvent() {

    }

    LzString WindowResizeEvent::toString() const {
        return "[WINDOW RESIZE EVENT] [ width: " + std::to_string(mWidth) + ", height: " + std::to_string(mHeight) + " ]";
    }

    bool WindowResizeEvent::isOfCategory(EventCategory category) const {
        return category == LZC_APPLICATION;
    }
}