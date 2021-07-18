#pragma once
#include <lafez/core/foundation/Window.hpp>
#include <lafez/core/foundation/WindowInfo.hpp>
#include <GLFW/glfw3.h>

namespace Lafez {
    class GlWindow final : public Window {
    public:
        GlWindow(const char* name, uint16_t width, uint16_t height);
        ~GlWindow();

        uint16_t getWidthImpl() const override;
        uint16_t getHeightImpl() const override;
        const LzString& getNameImpl() const override;
        void setNameImpl(const char* name) override;

        void initImpl() override;
        void terminateImpl() override;
        bool updateImpl() override;
        void closeImpl() override;

        void* getWindowPointerImpl() const override;

    private:
        GLFWwindow *mWindow;

        static bool sGLFWInitialized;

        void setup();
    };
};