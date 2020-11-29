#pragma once
#include <lafez/core/layers/Layer.hpp>
#include <lafez/core/lafez_window.hpp>

namespace Lafez {
    class LAFEZLIB ImGuiLayer : public Layer {
    public:
        ImGuiLayer(const LzString& tag, const LzShrPtr<Window>& window);
        ~ImGuiLayer();

        void onAttach() override;
        void onDetach() override;
        void onEvent(Event& event) const override;
        void onUpdate() const override;

    private:
        GLFWwindow* mWindow;
    };
};