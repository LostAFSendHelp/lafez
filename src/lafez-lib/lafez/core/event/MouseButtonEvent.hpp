#pragma once
#include <lafez/lafez_pch.hpp>
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB MouseButtonEvent : public Event {
    public:
        const int mButton;

        MouseButtonEvent(EventType type, int button);
        ~MouseButtonEvent();

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};