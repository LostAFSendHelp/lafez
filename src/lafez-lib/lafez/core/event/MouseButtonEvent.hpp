#pragma once
#include <lafez/lafez_pch.hpp>
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB MouseButtonEvent : public Event {
    public:
        const MouseButton mButton;

        MouseButtonEvent(EventType type, MouseButton button);
        ~MouseButtonEvent();

        std::string toString() const override;

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};