#include "EventSubscription.hpp"

namespace Lafez {
    uint16_t EventSubscription::sCount = 0;

    EventSubscription::EventSubscription(EventCallback callback):
    mCallback(callback),
    mIsAlive(true),
    mID(sCount++) {

    }

    EventSubscription::~EventSubscription() {

    }

    void EventSubscription::dispatch(Event& event) const {
        mCallback(event);
    }

    void EventSubscription::die() {
        mIsAlive = false;
    }

    bool EventSubscription::isAlive() const {
        return mIsAlive;
    }
}