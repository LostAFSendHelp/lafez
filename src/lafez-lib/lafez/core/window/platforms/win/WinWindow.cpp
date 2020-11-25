#include <lafez/utils/Log.hpp>
#include <lafez/core/lafez_event.hpp>
#include "WinWindow.hpp"

namespace Lafez {
    bool WinWindow::sGLFWInitialized = false;

    #ifdef __LZ_WIN

        Window* Window::createWindow(const char* name, uint16_t width, uint16_t height) {
            return new WinWindow(name, width, height);
        }

    #endif
    
    WindowInfo::WindowInfo(const char* name, uint16_t width, uint16_t height):
    mName(name),
    mWidth(width),
    mHeight(height),
    mShouldClose(false) {

    }

    WinWindow::WinWindow(const char* name, uint16_t width, uint16_t height):
    Window(),
    mInfo(new WindowInfo(name, width, height)),
    mWindow(nullptr) {

    }

    WinWindow::~WinWindow() {
        terminate();
    }

    uint16_t WinWindow::getWidth() const {
        return mInfo->mWidth;
    }

    uint16_t WinWindow::getHeight() const {
        return mInfo->mHeight;
    }

    const LzString& WinWindow::getName() const {
        return mInfo->mName;
    }

    bool WinWindow::shouldClose() const {
        return mInfo->mShouldClose;
    }

    void WinWindow::init() {
        if (!sGLFWInitialized) {
            auto result = glfwInit();
            LZ_ENGINE_ASSERT(result, "FAILED TO INITIALIZE GLFW");
        }

        if (mWindow != nullptr) return;

        mWindow = glfwCreateWindow(mInfo->mWidth, mInfo->mHeight, mInfo->mName.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(mWindow);
        glfwSetWindowUserPointer(mWindow, mInfo);
        setup();

        LZ_ENGINE_ASSERT(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "FAILED TO LOAD OPENGL FUNCTIONS");
        LZ_ENGINE_INFO("OPENGL version {0}", glGetString(GL_VERSION));
        glViewport(0, 0, mInfo->mWidth, mInfo->mHeight);
    }

    void WinWindow::terminate() {
        if (mWindow != nullptr) {
            glfwDestroyWindow(mWindow);
            mWindow = nullptr;
        }
    }

    void WinWindow::update() const {
        LZ_ENGINE_ASSERT(mWindow, "GLFW WINDOW NOT INITIALIZED FOR UPDATING");
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    void WinWindow::close() {
        if (mWindow == nullptr) {
            LZ_ENGINE_WARN("ATTEMPTING TO CLOSE UNINITIALIZED WINDOW");
        }

        mInfo->mShouldClose = true;
    }

    void WinWindow::setup() {
        // GLFW error
        glfwSetErrorCallback([](int code, const char* message) {
            LZ_ENGINE_ERR("GLFW WINDOW ERROR [code {0}]: {1}", code, message);
        });

        if (mWindow == nullptr) {
            LZ_ENGINE_WARN("GLFW WINDOW NOT INITIALIZED, CALLBACKS WILL NOT REGISTER");
        }
        
        glfwSetKeyCallback(mWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            auto keyAction = LZ_BUTTON_UNKNOWN;

            switch (action) {
            case GLFW_PRESS:
                keyAction = LZ_BUTTON_PRESS;
                break;

            case GLFW_RELEASE:
                keyAction = LZ_BUTTON_RELEASE;
                break;

            case GLFW_REPEAT:
                keyAction = LZ_BUTTON_REPEAT;
                break;
            
            default:
                break;
            }

            KeyEvent event{ key, keyAction };
            EventCenter::getInstance()->emit(event);
        });

        glfwSetMouseButtonCallback(mWindow, [](GLFWwindow *window, int button, int action, int mods) {
            auto mouseButton = LZ_MOUSE_UNKNOWN;
            auto mouseButtonAction = LZ_BUTTON_UNKNOWN;

            switch (action) {
            case GLFW_PRESS:
                mouseButtonAction = LZ_BUTTON_PRESS;
                break;

            case GLFW_RELEASE:
                mouseButtonAction = LZ_BUTTON_RELEASE;
                break;

            case GLFW_REPEAT:
                mouseButtonAction = LZ_BUTTON_REPEAT;
                break;

            default:
                break;
            }

            switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                mouseButton = LZ_MOUSE_LEFT;
                break;

            case GLFW_MOUSE_BUTTON_RIGHT:
                mouseButton = LZ_MOUSE_RIGHT;
                break;

            case GLFW_MOUSE_BUTTON_MIDDLE:
                mouseButton = LZ_MOUSE_MID;
                break;

            default:
                break;
            }

            MouseButtonEvent event{ mouseButton, mouseButtonAction };
            EventCenter::getInstance()->emit(event);
        });

        glfwSetScrollCallback(mWindow, [](GLFWwindow *window, double offsetX, double offsetY) {
            MouseScrollEvent event{ (float)offsetY };
            EventCenter::getInstance()->emit(event);
        });
        
        glfwSetCursorPosCallback(mWindow, [](GLFWwindow *window, double x, double y) {
            MouseMoveEvent event{ (float)x, (float)y };
            EventCenter::getInstance()->emit(event);
        });

        glfwSetWindowSizeCallback(mWindow, [](GLFWwindow *window, int width, int height) {
            auto& info = *((WindowInfo*)glfwGetWindowUserPointer(window));
            info.mWidth = width;
            info.mHeight = height;

            WindowResizeEvent event{ width, height };
            EventCenter::getInstance()->emit(event);
        });

        glfwSetWindowCloseCallback(mWindow,[](GLFWwindow *window) {
            WindowCloseEvent event{ };
            EventCenter::getInstance()->emit(event);
        });
    }
}