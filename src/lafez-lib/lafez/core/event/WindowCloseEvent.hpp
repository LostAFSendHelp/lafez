#pragma once
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB WindowCloseEvent : public Event {
    public:
        const bool mWindowShouldClose;

        WindowCloseEvent(bool shouldClose = true);
        ~WindowCloseEvent();

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};