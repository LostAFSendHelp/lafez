#include <lafez/utils/Log.hpp>
#include "Event.hpp"

namespace Lafez {
    Event::Event(EventType type):
    mType(type),
    mIsHandled(false) {

    }

    Event::~Event() {

    }

    bool Event::isHandled() const {
        return mIsHandled;
    }

    void Event::handle() {
        mIsHandled = true;
    }
}