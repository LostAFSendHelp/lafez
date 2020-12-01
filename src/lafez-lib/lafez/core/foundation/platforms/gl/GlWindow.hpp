#pragma once
#include <lafez/core/foundation/Window.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Lafez {
    struct WindowInfo {
        const LzString mName;
        uint16_t mWidth;
        uint16_t mHeight;
        bool mShouldClose;

        WindowInfo(const char* name, uint16_t width, uint16_t height);
    };

    class GlWindow final : public Window {
    public:
        GlWindow(const char* name, uint16_t width, uint16_t height);
        ~GlWindow();

        uint16_t getWidthImpl() const override;
        uint16_t getHeightImpl() const override;
        const LzString& getNameImpl() const override;
        bool shouldCloseImpl() const override;

        void initImpl() override;
        void terminateImpl() override;
        void updateImpl() override;
        void closeImpl() override;

        void* getWindowPointerImpl() const override;

    private:
        WindowInfo *mInfo;
        GLFWwindow *mWindow;

        static bool sGLFWInitialized;

        void setup();
    };
};