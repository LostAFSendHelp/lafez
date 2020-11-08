#pragma once
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB MouseMoveEvent : public Event {
    public:
        const float mX;
        const float mY;

        MouseMoveEvent(float x, float y);
        ~MouseMoveEvent();

        bool isOfCategory(EventCategory category) const override;

    private:

    };
};