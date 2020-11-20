#include "MouseButtonEvent.hpp"

namespace Lafez {
    MouseButtonEvent::MouseButtonEvent(MouseButton button, ButtonAction action):
    Event(LZT_MOUSE_BUTTON),
    mButton(button),
    mAction(action) {

    }

    MouseButtonEvent::~MouseButtonEvent() {

    }

    LzString MouseButtonEvent::toString() const {
        LzString buttonName{ "UNKNOWN" };
        switch (mButton) {
        case LZ_MOUSE_LEFT:
            buttonName = "LEFT";
            break;

        case LZ_MOUSE_RIGHT:
            buttonName = "RIGHT";
            break;

        case LZ_MOUSE_MID:
            buttonName = "MIDDLE";
            break;

        default:
            break;
        }

        LzString action{ "UNKNOWN" };
        switch (mAction) {
        case LZ_BUTTON_PRESS:
            action = "PRESS";
            break;

        case LZ_BUTTON_RELEASE:
            action = "RELEASE";
            break;

        case LZ_BUTTON_REPEAT:
            action = "REPEAT";
            break;

        default:
            break;
        }

        return "[MOUSE BUTTON EVENT] [ button: " + buttonName + ", action: " + action + " ]";
    }

    bool MouseButtonEvent::isOfCategory(EventCategory category) const {
        return category == LZC_INPUT || category == LZC_MOUSE;
    }
}