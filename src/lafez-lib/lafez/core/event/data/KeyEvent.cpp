#include "KeyEvent.hpp"

namespace Lafez {
    KeyEvent::KeyEvent(int keyCode, ButtonAction action):
    Event(LZT_KEY),
    mKeyCode(keyCode),
    mAction(action) {

    }

    KeyEvent::~KeyEvent() {

    }

    std::string KeyEvent::toString() const {
        std::string action{ "UNKNOWN" };
        
        switch (mAction)
        {
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

        return "[KEY EVENT] [ key: " + std::to_string(mKeyCode) + ", action: " + action + " ]";
    }

    bool KeyEvent::isOfCategory(EventCategory category) const {
        return category == LZC_KEY || category == LZC_INPUT;
    }
}