#pragma once
#include <lafez/core/window/Window.hpp>
#include <GLFW/glfw3.h>

namespace Lafez {
    struct WindowInfo {
        const LzString mName;
        uint16_t mWidth;
        uint16_t mHeight;
        bool mShouldClose;

        WindowInfo(const char* name, uint16_t width, uint16_t height);
    };

    class LAFEZLIB WinWindow final : public Window {
    public:
        WinWindow(const char* name, uint16_t width, uint16_t height);
        ~WinWindow();

        uint16_t getWidth() const override;
        uint16_t getHeight() const override;
        const LzString& getName() const override;
        bool shouldClose() const override;

        void init() override;
        void terminate() override;
        void update() const override;
        void close() override;

    private:
        WindowInfo *mInfo;
        GLFWwindow *mWindow;

        static bool sGLFWInitialized;

        void setup();
    };
};