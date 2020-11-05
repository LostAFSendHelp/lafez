#include "ApplicationEvent.hpp"

namespace Lafez {
    ApplicationEvent::ApplicationEvent(EventType type, bool shouldClose, int width, int height):
    Event(type),
    mWindowShouldClose(shouldClose),
    mWidth(width),
    mHeight(height) {
        auto rawValue = static_cast<uint8_t>(mType);
        if (rawValue < 30) {
            mType = EventType::None;
        }
    }

    ApplicationEvent::~ApplicationEvent() {

    }

    bool ApplicationEvent::isOfCategory(EventCategory category) const {
        return category == EventCategory::Application;
    }
}