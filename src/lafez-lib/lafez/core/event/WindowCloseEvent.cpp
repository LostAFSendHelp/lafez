#include "WindowCloseEvent.hpp"

namespace Lafez {
    WindowCloseEvent::WindowCloseEvent(bool shouldClose):
    Event(EventType::WindowClose),
    mWindowShouldClose(shouldClose) {

    }

    WindowCloseEvent::~WindowCloseEvent() {

    }

    bool WindowCloseEvent::isOfCategory(EventCategory category) const {
        return category == EventCategory::Application;
    }
}