#include "WindowCloseEvent.hpp"

namespace Lafez {
    WindowCloseEvent::WindowCloseEvent():
    Event(EventType::WindowClose) {

    }

    WindowCloseEvent::~WindowCloseEvent() {

    }

    std::string WindowCloseEvent::toString() const {
        return "[WINDOW CLOSE EVENT]";
    }

    bool WindowCloseEvent::isOfCategory(EventCategory category) const {
        if (mType == EventType::None) {
            return category == EventCategory::None;
        } else {
            return category == EventCategory::Application;
        }
    }
}