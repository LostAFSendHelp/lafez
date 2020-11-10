#include "MouseMoveEvent.hpp"

namespace Lafez {
    MouseMoveEvent::MouseMoveEvent(float x, float y):
    Event(EventType::MouseMove),
    mX(x),
    mY(y) {

    }

    MouseMoveEvent::~MouseMoveEvent() {

    }

    bool MouseMoveEvent::isOfCategory(EventCategory category) const {
        if (mType == EventType::None) {
            return category == EventCategory::None;
        } else {
            return category == EventCategory::Input || category == EventCategory::MouseInput;
        }
    }
}