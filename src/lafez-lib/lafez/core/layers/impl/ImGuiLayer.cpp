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
        ImGuiBackend::init();

        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigDockingWithShift = false;
    }

    void ImGuiLayer::onDetach() {
        ImGuiBackend::terminate();
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

        static float z;
        ImGui::Begin("Another");
        ImGui::SliderFloat("Slide", &z, .0f, 1.0f, NULL, 1.0f);
        ImGui::SliderFloat("AnotherSlide", &z, .0f, 1.0f, NULL, 1.0f);
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGuiBackend::renderDrawData(ImGui::GetDrawData());
    }
}