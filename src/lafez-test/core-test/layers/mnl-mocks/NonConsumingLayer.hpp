#pragma once
#include <lafez/core/lafez_layer.hpp>

namespace Lafez {
    class NonConsumingLayer : public Layer {
    public:
        bool mAttached;
        mutable bool mWasFedEvent;

        NonConsumingLayer(const char *name = "NonConsumingLayer"):
        Layer(name),
        mAttached(false),
        mWasFedEvent(false) {

        }

        ~NonConsumingLayer() {

        }

    protected:
        void onAttach() override {
            mAttached = true;
        }

        void onDetach() override {
            mAttached = false;
        }

        void onEvent(Event& event) const override {
            mWasFedEvent = true;
        }

    private:

    };
};