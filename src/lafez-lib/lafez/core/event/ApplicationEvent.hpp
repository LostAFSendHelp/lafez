#pragma once
#include "Event.hpp"

namespace Lafez {
    class ApplicationEvent : public Event {
    public:
        const bool mWindowShouldClose;
        const int mWidth;
        const int mHeight;

        ApplicationEvent(EventType type, bool shouldClose, int width, int height);
        ~ApplicationEvent();

        bool isOfCategory(EventCategory category) const override;

    private:

    };
};