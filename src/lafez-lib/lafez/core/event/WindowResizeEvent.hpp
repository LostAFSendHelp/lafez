#pragma once
#include "Event.hpp"

namespace Lafez {
    class LAFEZLIB WindowResizeEvent : public Event {
    public:
        const int mWidth;
        const int mHeight;

        WindowResizeEvent(int width, int height);
        ~WindowResizeEvent();

        std::string toString() const override;

    protected:
        bool isOfCategory(EventCategory category) const override;

    private:

    };
};