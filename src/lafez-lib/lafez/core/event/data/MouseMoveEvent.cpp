#include "MouseMoveEvent.hpp"

namespace Lafez {
    MouseMoveEvent::MouseMoveEvent(float x, float y):
    Event(LZT_MOUSE_MOVE),
    mX(x),
    mY(y) {

    }

    MouseMoveEvent::~MouseMoveEvent() {

    }

    std::string MouseMoveEvent::toString() const {
        return "[MOUSE MOVE EVENT] [ x: " + std::to_string(mX) + ", y: " + std::to_string(mY) + " ]";
    }

    bool MouseMoveEvent::isOfCategory(EventCategory category) const {
        return category == LZC_INPUT || category == LZC_MOUSE;
    }
}