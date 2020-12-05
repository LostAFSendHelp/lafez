#pragma once
#include <lafez/core/foundation/Input.hpp>

namespace Lafez {
    class InputMock : public Input {
    public:
        InputMock(int* ref):
        mRef(ref) {

        }

        ~InputMock() {

        }

    protected:
        void initImpl() override {
            *mRef = 100;
        }

        void terminateImpl() override {
            *mRef = -100;
        }

        LzPair<float, float> getMousePositionImpl() const override {
            return { .5f, .5f };
        }

        bool getKeyImpl(int keycode) const override {
            return true;
        }

    private:
        int* mRef;

    };
};