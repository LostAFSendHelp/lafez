#include "KeyEvent.hpp"

namespace Lafez {
    KeyEvent::KeyEvent(EventType type, int keyCode):
    Event(
        [](const EventType& type) {
            auto rawValue = static_cast<uint8_t>(type);
            return (rawValue >= 10 && rawValue < 20) ? type : EventType::None;
        }(type)
    ),
    mKeyCode((mType != EventType::None) ? keyCode : -1) {

    }

    KeyEvent::~KeyEvent() {

    }

    std::string KeyEvent::toString() const {
        if (mType == EventType::None) {
            return "[INVALID KEY EVENT]";
        }

        std::string action{ "REPEAT" };
        switch (mType)
        {
        case EventType::KeyDown:
            action = "DOWN";
            break;

        case EventType::KeyUp:
            action = "UP";
            break;

        default:
            break;
        }

        return "[KEY EVENT] [ key: " + std::to_string(mKeyCode) + ", action: " + action + " ]";
    }

    bool KeyEvent::isOfCategory(EventCategory category) const {
        if (mType == EventType::None) {
            return category == EventCategory::None;
        } else {
            return category == EventCategory::Input || category == EventCategory::KeyInput;
        }
    }
}