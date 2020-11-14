#include "MouseScrollEvent.hpp"

namespace Lafez {
    MouseScrollEvent::MouseScrollEvent(float offset):
    Event(EventType::MouseScroll),
    mOffset(offset) {

    }

    MouseScrollEvent::~MouseScrollEvent() {

    }

    std::string MouseScrollEvent::toString() const {
        return "[MOUSE SCROLL EVENT] [ offset: " + std::to_string(mOffset) + " ]";
    }

    bool MouseScrollEvent::isOfCategory(EventCategory category) const {
        if (mType == EventType::None) {
            return category == EventCategory::None;
        } else {
            return category == EventCategory::Input || category == EventCategory::MouseInput;
        }
    }
}