#pragma once
#include <lafez/platform_headers/lafez_gl.hpp>
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