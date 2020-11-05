#include "MouseEvent.hpp"

namespace Lafez {
    MouseEvent::MouseEvent(EventType type, int button, float x, float y):
    Event(type),
    mButton(button),
    mX(x),
    mY(y) {
        auto rawValue = static_cast<uint8_t>(mType);
        if (rawValue < 20 || rawValue >= 30) {
            mType = EventType::None;
        }
    }

    MouseEvent::~MouseEvent() {

    }

    bool MouseEvent::isOfCategory(EventCategory category) const {
        return category == EventCategory::Input || category == EventCategory::MouseInput;
    }
}