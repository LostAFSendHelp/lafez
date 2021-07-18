#include <lafez/utils/Log.hpp>
#include <lafez-imgui/impl/imgui_impl_glfw.h>
#include <lafez-imgui/impl/imgui_impl_opengl3.h>
#include "GlImGui.hpp"

namespace Lafez {
    GlImGui::GlImGui(GLFWwindow* window):
    ImGuiBackend(),
    mWindow(window) {
        LZ_ENGINE_ASSERT(window, "ATTEMPTING TO INITIALIZE GLIMGUI TO NULLPTR");
    }

    GlImGui::~GlImGui() {
        terminateImpl();
    }

    void GlImGui::initImpl() {
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
        ImGui_ImplOpenGL3_Init();
        LZ_ENGINE_INFO("GL IMGUI INITIALIZED");
    }

    void GlImGui::terminateImpl() {
        if (ImGui::GetCurrentContext() != nullptr) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            LZ_ENGINE_INFO("GL IMGUI TERMINATED");
        }
    }

    void GlImGui::newFrameImpl() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
    }

    void GlImGui::renderDrawDataImpl(ImDrawData* data) {
        ImGui_ImplOpenGL3_RenderDrawData(data);
    }
}