#pragma once
#include <lafez/core/lafez_layer.hpp>

namespace Lafez {
    class ConsumingLayer : public Layer {
    public:
        bool mAttached;
        mutable bool mWasFedEvent;

        ConsumingLayer(const char *name = "ConsumingLayer"):
        Layer(name),
        mAttached(false),
        mWasFedEvent(false) {

        }

        ~ConsumingLayer() {

        }

    protected:
        void onAttach() override {
            mAttached = true;
        }

        void onDetach() override {
            mAttached = false;
        }

        void onEvent(Event& event) const override {
            event.handle();
            mWasFedEvent = true;
        }

    private:

    };
};