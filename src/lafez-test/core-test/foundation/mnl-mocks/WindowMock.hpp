#pragma once
#include <lafez/core/foundation/Window.hpp>

namespace Lafez {
    class WindowMock : public Window {
    public:
        WindowMock(const char* name, int width, int height, int* ref):
        mRef(ref),
        mName(name) {

        }

        ~WindowMock() {

        }

    protected:
        uint16_t getWidthImpl() const override {
            return 99;
        }

        uint16_t getHeightImpl() const override {
            return 99;
        }

        const LzString& getNameImpl() const override {
            return mName;
        }

        bool shouldCloseImpl() const override {
            return false;
        }

        void* getWindowPointerImpl() const override {
            return mRef;
        }

        void updateImpl() override {
            ++(*mRef);
        }

        void closeImpl() override {
            --(*mRef);
        }

        void initImpl() override {
            *mRef = 100;
        }

        void terminateImpl() override {
            *mRef = -100;
        }

    private:
        int* mRef;
        LzString mName;
    };
};