#include "MouseScrollEvent.hpp"

namespace Lafez {
    MouseScrollEvent::MouseScrollEvent(float offset):
    Event(LZT_MOUSE_SCROLL),
    mOffset(offset) {

    }

    MouseScrollEvent::~MouseScrollEvent() {

    }

    std::string MouseScrollEvent::toString() const {
        return "[MOUSE SCROLL EVENT] [ offset: " + std::to_string(mOffset) + " ]";
    }

    bool MouseScrollEvent::isOfCategory(EventCategory category) const {
        return category == LZC_INPUT || category == LZC_MOUSE;
    }
}