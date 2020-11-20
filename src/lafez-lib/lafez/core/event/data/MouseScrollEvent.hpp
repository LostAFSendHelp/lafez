#pragma once
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB MouseScrollEvent : public Event {
    public:
        const float mOffset;

        MouseScrollEvent(float offset);
        ~MouseScrollEvent();

        LzString toString() const override;

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:
    
    };
};