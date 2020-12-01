#pragma once
#include <GLFW/glfw3.h>
#include <lafez/core/foundation/ImGuiBackend.hpp>

namespace Lafez {
    class GlImGui : public ImGuiBackend {
    public:
        GlImGui(GLFWwindow* window);
        ~GlImGui();

    protected:
        void initImpl() override;
        void terminateImpl() override;
        void newFrameImpl() override;
        void renderDrawDataImpl(ImDrawData* data) override;

    private:
        GLFWwindow* mWindow;
    };
};