#pragma once
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB MouseMoveEvent : public Event {
    public:
        const float mX;
        const float mY;

        MouseMoveEvent(float x, float y);
        ~MouseMoveEvent();

        LzString toString() const override;

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};