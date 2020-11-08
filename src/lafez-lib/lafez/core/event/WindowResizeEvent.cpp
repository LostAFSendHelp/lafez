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
        return category == EventCategory::Application;
    }
}