#include "MouseButtonEvent.hpp"

namespace Lafez {
    MouseButtonEvent::MouseButtonEvent(EventType type, int button):
    Event(type),
    mButton(button) {
        auto rawValue = static_cast<uint8_t>(mType);
        if (rawValue < 20 || rawValue >= 30) {
            mType = EventType::None;
        }
    }

    MouseButtonEvent::~MouseButtonEvent() {

    }

    bool MouseButtonEvent::isOfCategory(EventCategory category) const {
        return category == EventCategory::Input || category == EventCategory::MouseInput;
    }
}