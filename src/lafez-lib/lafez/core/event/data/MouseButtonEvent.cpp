#include "MouseButtonEvent.hpp"

namespace Lafez {
    MouseButtonEvent::MouseButtonEvent(EventType type, MouseButton button):
    Event(
        [](const EventType& type) {
            auto rawValue = static_cast<uint8_t>(type);
            return (rawValue >= 20 && rawValue < 30) ? type : EventType::None;
        }(type)
    ),
    mButton(mType != EventType::None ? button : MouseButton::Unknown) {

    }

    MouseButtonEvent::~MouseButtonEvent() {

    }

    std::string MouseButtonEvent::toString() const {
        if (mType == EventType::None) {
            return "[INVALID MOUSE EVENT]";
        }

        std::string buttonName{ "UNKNOWN" };
        switch (mButton) {
        case MouseButton::Left:
            buttonName = "LEFT";
            break;

        case MouseButton::Right:
            buttonName = "RIGHT";
            break;

        case MouseButton::Mid:
            buttonName = "MIDDLE";
            break;

        default:
            break;
        }

        std::string action{ "UP" };
        switch (mType) {
        case EventType::MouseDown:
            action = "DOWN";
            break;

        default:
            break;
        }

        return "[MOUSE BUTTON EVENT] [ button: " + buttonName + ", action: " + action + " ]";
    }

    bool MouseButtonEvent::isOfCategory(EventCategory category) const {
        if (mType == EventType::None) {
            return category == EventCategory::None;
        } else {
            return category == EventCategory::Input || category == EventCategory::MouseInput;
        }
    }
}