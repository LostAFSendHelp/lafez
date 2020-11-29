#include "Layer.hpp"

namespace Lafez {
    uint8_t Layer::sCount = 0;

    Layer::Layer(const LzString& tag):
    mID(sCount++),
    mTag(tag),
    mIsEnabled(true),
    mIsHidden(false) {

    }

    Layer::~Layer() {

    }

    void Layer::onAttach() {

    }

    void Layer::onDetach() {

    }

    void Layer::onEvent(Event& event) const {
        
    }

    void Layer::onUpdate() const {

    }
}