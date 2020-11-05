#include <lafez/utils/Log.hpp>
#include "Event.hpp"

namespace Lafez {
    long Event::sCount = 0;

    Event::Event(EventType type):
    mID(sCount++),
    mType(type),
    mHandled(false) {
        LZ_ENGINE_INFO("LafezEvent created with ID {0}", mID);
    }

    Event::~Event() {

    }
}