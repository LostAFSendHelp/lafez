#include "KeyEvent.hpp"

namespace Lafez {
    KeyEvent::KeyEvent(EventType type, int keyCode):
    Event(type),
    mKeyCode(keyCode) {
        auto rawValue = static_cast<uint8_t>(mType);
        if (rawValue < 10 || rawValue >= 20) {
            mType = EventType::None;
        }
    }

    KeyEvent::~KeyEvent() {

    }

    bool KeyEvent::isOfCategory(EventCategory category) const {
        return category == EventCategory::Input || category == EventCategory::KeyInput;
    }
}