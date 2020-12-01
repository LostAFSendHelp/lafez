#pragma once
#include <GLFW/glfw3.h>
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