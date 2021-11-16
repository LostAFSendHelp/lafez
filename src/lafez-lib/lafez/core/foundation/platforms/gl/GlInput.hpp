#pragma once
#include <lafez/platform_headers/lafez_gl.hpp>
#include <lafez/core/foundation/Input.hpp>

namespace Lafez {
    class GlInput : public Input {
    public:
        GlInput(GLFWwindow* window);
        ~GlInput();

    protected:
        void initImpl() override;
        void terminateImpl() override;
        bool getKeyImpl(int keycode) const override;
        LzPair<float, float> getMousePositionImpl() const override;

    private:
        GLFWwindow* mWindow;
    };
};