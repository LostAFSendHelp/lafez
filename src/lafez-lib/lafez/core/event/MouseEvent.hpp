#pragma once
#include <lafez/lafez-pch.hpp>
#include "Event.hpp"

namespace Lafez {
    class MouseEvent : public Event {
    public:
        const int mButton;
        const float mX, mY;

        MouseEvent(EventType type, int button, float x, float y);
        ~MouseEvent();

        bool isOfCategory(EventCategory category) const override;

    private:

    };
};