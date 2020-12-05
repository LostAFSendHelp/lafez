#pragma once
#include <lafez/core/foundation/ImGuiBackend.hpp>

namespace Lafez {
    class ImGuiBackendMock : public ImGuiBackend {
    public:
        ImGuiBackendMock(int* ref):
        mRef(ref) {

        }

        ~ImGuiBackendMock() {

        }

    protected:
        void initImpl() override {
            *mRef = 100;
        }

        void terminateImpl() override {
            *mRef = -100;
        }

        void newFrameImpl() override {
            *mRef = 200;
        }

        void renderDrawDataImpl(ImDrawData* data) override {
            *mRef = -200;
        }

    private:
        int* mRef;

    };
};