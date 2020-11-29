#include "ImGuiLayer.hpp"
#include <lafez/utils/Log.hpp>
#include <lafez-imgui/impl/imgui_impl_opengl3.h>
#include <lafez-imgui/impl/imgui_impl_glfw.h>

namespace Lafez {
    ImGuiLayer::ImGuiLayer(const LzString& tag, const LzShrPtr<Window>& window):
    Layer(tag),
    mWindow(nullptr) {
        #ifdef __LZ_WIN
            if (auto w = std::dynamic_pointer_cast<WinWindow>(window)) {
                mWindow = w->getGLFWwindow();
            }
        #endif
        
        if (mWindow == nullptr) {
            LZ_ENGINE_WARN("IMGUI WINDOW INITIALIZED TO NULLPTR");
        }
    }

    ImGuiLayer::~ImGuiLayer() {

    }

    void ImGuiLayer::onAttach() {
        if (mWindow == nullptr) return;
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
        ImGui_ImplOpenGL3_Init();
    }

    void ImGuiLayer::onDetach() {
        if (mWindow == nullptr) return;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::onEvent(Event& event) const {

    }

    void ImGuiLayer::onUpdate() const {
        if (mWindow == nullptr) return;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}