#pragma once 
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB KeyEvent : public Event {
    public:
        const int mKeyCode;
        const ButtonAction mAction;
        
        KeyEvent(int keyCode, ButtonAction action);
        ~KeyEvent();

        LzString toString() const override;

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};