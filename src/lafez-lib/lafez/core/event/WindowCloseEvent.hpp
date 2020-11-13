#pragma once
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB WindowCloseEvent : public Event {
    public:
        WindowCloseEvent();
        ~WindowCloseEvent();

        std::string toString() const override;

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};