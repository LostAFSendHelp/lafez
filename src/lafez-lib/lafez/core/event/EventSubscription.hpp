#pragma once
#include "Event.hpp"

namespace Lafez {
    using EventCallback = std::function<void(Event&)>;

    class EventSubscription final {
    public:
        const uint16_t mID;

        EventSubscription(EventCallback callback);
        ~EventSubscription();

        void dispatch(Event& event) const;
        void die();
        bool isAlive() const;

    private:
        EventCallback mCallback;
        bool mIsAlive;
        static uint16_t sCount;
    };
};