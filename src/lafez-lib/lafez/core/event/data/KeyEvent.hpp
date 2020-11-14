#pragma once 
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB KeyEvent : public Event {
    public:
        const int mKeyCode;
        
        KeyEvent(EventType type, int keyCode);
        ~KeyEvent();

        std::string toString() const override;

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};