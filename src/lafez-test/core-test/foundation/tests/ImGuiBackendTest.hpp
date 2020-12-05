#pragma once
#include <lafez_test_pch.hpp>
#include <core-test/foundation/mnl-mocks/ImGuiBackendMock.hpp>

namespace Lafez {
    TEST(ImGuiBackend, ShouldCallSingletonFunctionsIfInitialized) {
        EXPECT_FALSE(ImGuiBackend::isInitialized());
        
        int val = 0;
        ImGuiBackend::startUp<ImGuiBackendMock>(&val);
        EXPECT_TRUE(ImGuiBackend::isInitialized());
        
        ImGuiBackend::init();
        EXPECT_EQ(val, 100);
        ImGuiBackend::newFrame();
        EXPECT_EQ(val, 200);
        ImGuiBackend::renderDrawData(nullptr);
        EXPECT_EQ(val, -200);
        ImGuiBackend::terminate();
        EXPECT_EQ(val, -100);
        ImGuiBackend::shutDown();
        EXPECT_FALSE(ImGuiBackend::isInitialized());
    }
};