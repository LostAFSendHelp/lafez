#pragma once
#include <lafez/core/lafez_event.hpp>
#include <lafez_test_pch.hpp>

namespace Lafez {
    class KeyEventTest : public ::testing::Test {
    public:
        KeyEvent mKeyPress, mKeyRelease, mKeyRepeat;

        KeyEventTest():
        mKeyPress(81, LZ_BUTTON_PRESS),
        mKeyRelease(81, LZ_BUTTON_RELEASE),
        mKeyRepeat(81, LZ_BUTTON_REPEAT) {

        }

        ~KeyEventTest() {

        }

    protected:
        void SetUp() override {

        }

        void TearDown() override {

        }
    };

    TEST_F(KeyEventTest, ReturnsCorrectType) {
        EXPECT_EQ(mKeyPress.mType, LZT_KEY);
        EXPECT_EQ(mKeyRelease.mType, LZT_KEY);
        EXPECT_EQ(mKeyRepeat.mType, LZT_KEY);
    }

    TEST_F(KeyEventTest, ReturnsCorrectCategories) {
        EXPECT_TRUE(mKeyPress.isOfCategories(LZC_KEY, LZC_INPUT));
        EXPECT_TRUE(mKeyRelease.isOfCategories(LZC_KEY, LZC_INPUT));
        EXPECT_TRUE(mKeyRepeat.isOfCategories(LZC_KEY, LZC_INPUT));
    }

    TEST_F(KeyEventTest, ReturnsCorrectInfo) {
        EXPECT_EQ(mKeyPress.mKeyCode, 81);
        EXPECT_EQ(mKeyRelease.mKeyCode, 81);
        EXPECT_EQ(mKeyRepeat.mKeyCode, 81);
    }
};