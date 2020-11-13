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

    const std::string& WinWindow::getName() const {
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
            auto type = EventType::None;
            
            switch (action) {
            case GLFW_PRESS:
                type = EventType::KeyDown;
                break;

            case GLFW_RELEASE:
                type = EventType::KeyUp;
                break;

            case GLFW_REPEAT:
                type = EventType::KeyRepeat;
                break;
            
            default:
                break;
            }

            KeyEvent event{ type, key };
            EventCenter::getInstance()->emit(event);
        });

        glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
            auto type = EventType::None;
            auto mouseButton = MouseButton::Unknown;

            switch (action) {
            case GLFW_PRESS:
                type = EventType::MouseDown;
                break;

            case GLFW_RELEASE:
                type = EventType::MouseUp;
                break;

            default:
                break;
            }

            switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                mouseButton = MouseButton::Left;
                break;

            case GLFW_MOUSE_BUTTON_RIGHT:
                mouseButton = MouseButton::Right;
                break;

            case GLFW_MOUSE_BUTTON_MIDDLE:
                mouseButton = MouseButton::Mid;
                break;

            default:
                break;
            }

            MouseButtonEvent event{ type, mouseButton };
            EventCenter::getInstance()->emit(event);
        });
        
        glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double x, double y) {
            MouseMoveEvent event{ (float)x, (float)y };
            EventCenter::getInstance()->emit(event);
        });

        glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
            auto& info = *((WindowInfo*)glfwGetWindowUserPointer(window));
            info.mWidth = width;
            info.mHeight = height;

            WindowResizeEvent event{ width, height };
            EventCenter::getInstance()->emit(event);
        });

        glfwSetWindowCloseCallback(mWindow,[](GLFWwindow* window) {
            WindowCloseEvent event{ };
            EventCenter::getInstance()->emit(event);
        });
    }
}