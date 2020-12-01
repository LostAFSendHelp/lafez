#include <lafez/utils/Log.hpp>
#include "GlInput.hpp"

namespace Lafez {
    GlInput::GlInput(GLFWwindow* window):
    Input(),
    mWindow(window) {
        LZ_ENGINE_ASSERT(mWindow, "ATTEMPTING TO INITIALIZE GLFW TO NULLPTR");
    }

    GlInput::~GlInput() {

    }

    void GlInput::initImpl() {

    }

    void GlInput::terminateImpl() {

    }

    bool GlInput::getKeyImpl(int keycode) const {
        return glfwGetKey(mWindow, keycode);
    }

    LzPair<float, float> GlInput::getMousePositionImpl() const {
        double x, y;
        glfwGetCursorPos(mWindow, &x, &y);
        return { (float)x, (float)y };
    }
}