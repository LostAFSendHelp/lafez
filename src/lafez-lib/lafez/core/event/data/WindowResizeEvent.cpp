#include "WindowResizeEvent.hpp"

namespace Lafez {
    WindowResizeEvent::WindowResizeEvent(int width, int height):
    Event(EventType::WindowResize),
    mWidth(width),
    mHeight(height) {

    }

    WindowResizeEvent::~WindowResizeEvent() {

    }

    std::string WindowResizeEvent::toString() const {
        return "[WINDOW RESIZE EVENT] [ width: " + std::to_string(mWidth) + ", height: " + std::to_string(mHeight) + " ]";
    }

    bool WindowResizeEvent::isOfCategory(EventCategory category) const {
        if (mType == EventType::None) {
            return category == EventCategory::None;
        } else {
            return category == EventCategory::Application;
        }
    }
}