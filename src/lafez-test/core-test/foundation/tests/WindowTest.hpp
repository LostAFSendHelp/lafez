#pragma once
#include <lafez_test_pch.hpp>
#include <lafez/core/lafez_foundation.hpp>
#include <core-test/foundation/mnl-mocks/WindowMock.hpp>

namespace Lafez {
    TEST(Window, ShouldNotCallFunctionsWithoutBeingInitialized) {
        EXPECT_FALSE(Window::isInitialized());
        EXPECT_EQ(Window::getWidth(), 0);
        EXPECT_EQ(Window::getHeight(), 0);
        EXPECT_EQ(Window::getWindowPointer(), nullptr);
        EXPECT_TRUE(Window::shouldClose());
    }

    TEST(Window, ShouldCallSingletonFunctions) {
        int val = 1000;
        Window::startUp<WindowMock>("test", 0, 0, &val);
        EXPECT_TRUE(Window::isInitialized());
        EXPECT_EQ(Window::getWidth(), 99);
        EXPECT_EQ(Window::getHeight(), 99);
        EXPECT_EQ(*(static_cast<int*>(Window::getWindowPointer())), 100);
        EXPECT_FALSE(Window::shouldClose());
        
        Window::update();
        EXPECT_EQ(val, 101);
        Window::close();
        EXPECT_EQ(val, 100);
        Window::shutDown();
        EXPECT_EQ(val, -100);
        EXPECT_FALSE(Window::isInitialized());
        Window::update();
        EXPECT_EQ(val, -100);
    }
};