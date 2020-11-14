#include "WindowCloseEvent.hpp"

namespace Lafez {
    WindowCloseEvent::WindowCloseEvent():
    Event(LZT_WINDOW_CLOSE) {

    }

    WindowCloseEvent::~WindowCloseEvent() {

    }

    std::string WindowCloseEvent::toString() const {
        return "[WINDOW CLOSE EVENT]";
    }

    bool WindowCloseEvent::isOfCategory(EventCategory category) const {
        return category == LZC_APPLICATION;
    }
}