#include <lafez/utils/Log.hpp>
#include <lafez/core/lafez_foundation.hpp>
#include "ImGuiLayer.hpp"

namespace Lafez {
    ImGuiLayer::ImGuiLayer(const LzString& tag):
    Layer(tag) {
        if (!ImGuiBackend::isInitialized()) {
            LZ_ENGINE_WARN("IMGUIBACKEND NOT INITIALIZED, IMGUI FUNCTIONALITIES WILL NOT WORK BACKEND IS INITIALIZED");
        }
    }

    ImGuiLayer::~ImGuiLayer() {

    }

    void ImGuiLayer::onAttach() {
        ImGui::CreateContext();
        ImGuiBackend::init();
    }

    void ImGuiLayer::onDetach() {
        ImGuiBackend::terminate();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::onEvent(Event& event) const {

    }

    void ImGuiLayer::onUpdate() const {
        ImGuiBackend::newFrame();
        ImGui::NewFrame();

        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGuiBackend::renderDrawData(ImGui::GetDrawData());
    }
}