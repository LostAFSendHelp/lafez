#pragma once
#include <lafez/lafez_pch.hpp>
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB MouseButtonEvent : public Event {
    public:
        const MouseButton mButton;
        const ButtonAction mAction;

        MouseButtonEvent(MouseButton button, ButtonAction action);
        ~MouseButtonEvent();

        LzString toString() const override;

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};