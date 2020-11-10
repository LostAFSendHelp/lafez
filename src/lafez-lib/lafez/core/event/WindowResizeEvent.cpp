#include "WindowResizeEvent.hpp"

namespace Lafez {
    WindowResizeEvent::WindowResizeEvent(int width, int height):
    Event(EventType::WindowResize),
    mWidth(width),
    mHeight(height) {

    }

    WindowResizeEvent::~WindowResizeEvent() {

    }

    bool WindowResizeEvent::isOfCategory(EventCategory category) const {
        if (mType == EventType::None) {
            return category == EventCategory::None;
        } else {
            return category == EventCategory::Application;
        }
    }
}