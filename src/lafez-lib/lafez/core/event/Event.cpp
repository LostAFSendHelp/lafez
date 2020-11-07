#include <lafez/utils/Log.hpp>
#include "Event.hpp"

namespace Lafez {
    long Event::sCount = 0;

    Event::Event(EventType type):
    mID(sCount++),
    mType(type),
    mIsHandled(false) {
        LZ_ENGINE_INFO("LafezEvent created with ID {0}", mID);
    }

    Event::~Event() {

    }

    bool Event::isHandled() const {
        return mIsHandled;
    }

    EventType Event::getType() const {
        return mType;
    }

    void Event::handle() {
        mIsHandled = true;
    }
}