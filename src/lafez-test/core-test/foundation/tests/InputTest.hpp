#pragma
#include <lafez_test_pch.hpp>
#include <core-test/foundation/mnl-mocks/InputMock.hpp>

namespace Lafez {
    TEST(Input, ShouldNotCallFunctionsWithoutBeingInitialized) {
        EXPECT_FALSE(Input::isInitialized());
        EXPECT_FALSE(Input::getKey(0));
        EXPECT_EQ(Input::getMousePosition(), (LzPair<float, float>{ .0f, .0f }));
    }

    TEST(Input, ShouldCallSingletonFunctions) {
        int val = 0;
        Input::startUp<InputMock>(&val);
        EXPECT_TRUE(Input::isInitialized());
        EXPECT_TRUE(Input::getKey(0));
        EXPECT_EQ(Input::getMousePosition(), (LzPair<float, float>{ .5f, .5f }));

        EXPECT_EQ(val, 100);
        Input::shutDown();
        EXPECT_FALSE(Input::isInitialized());
        EXPECT_EQ(val, -100);
        EXPECT_EQ(Input::getMousePosition(), (LzPair<float, float>{ .0f, .0f }));
    }
};