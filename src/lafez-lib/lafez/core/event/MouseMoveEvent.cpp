#include "MouseMoveEvent.hpp"

namespace Lafez {
    MouseMoveEvent::MouseMoveEvent(float x, float y):
    Event(EventType::MouseMove),
    mX(x),
    mY(y) {

    }

    MouseMoveEvent::~MouseMoveEvent() {

    }

    std::string MouseMoveEvent::toString() const {
        if (mType == EventType::None) {
            return "[INVALID MOUSE EVENT]";
        }

        return "[MOUSE MOVE EVENT] [ x: " + std::to_string(mX) + ", y: " + std::to_string(mY) + " ]";
    }

    bool MouseMoveEvent::isOfCategory(EventCategory category) const {
        if (mType == EventType::None) {
            return category == EventCategory::None;
        } else {
            return category == EventCategory::Input || category == EventCategory::MouseInput;
        }
    }
}