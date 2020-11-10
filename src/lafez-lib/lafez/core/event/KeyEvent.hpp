#pragma once 
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB KeyEvent : public Event {
    public:
        const int mKeyCode;
        
        KeyEvent(EventType type, int keyCode);
        ~KeyEvent();

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};