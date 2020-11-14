#pragma once
#include <lafez/core/lafez_event.hpp>
#include <lafez_test_pch.hpp>

namespace Lafez {
    class MouseEventTest : public ::testing::Test {
    public:
        MouseButtonEvent    mMousePress, mMouseRelease, mMouseRepeat;
        MouseMoveEvent      mMouseMove;
        MouseScrollEvent    mMouseScroll;

        MouseEventTest():
        mMousePress(LZ_MOUSE_LEFT, LZ_BUTTON_PRESS),
        mMouseRelease(LZ_MOUSE_RIGHT, LZ_BUTTON_RELEASE),
        mMouseRepeat(LZ_MOUSE_MID, LZ_BUTTON_REPEAT),
        mMouseMove(.0f, .0f),
        mMouseScroll(1.0f) {

        }

        ~MouseEventTest() {

        }

    protected:
        void SetUp() override {

        }

        void TearDown() override {

        }
    };

    TEST_F(MouseEventTest, ReturnsCorrectType) {
        EXPECT_EQ(mMousePress.mType, LZT_MOUSE_BUTTON);
        EXPECT_EQ(mMouseRelease.mType, LZT_MOUSE_BUTTON);
        EXPECT_EQ(mMouseRepeat.mType, LZT_MOUSE_BUTTON);
        EXPECT_EQ(mMouseMove.mType, LZT_MOUSE_MOVE);
        EXPECT_EQ(mMouseScroll.mType, LZT_MOUSE_SCROLL);
    }

    TEST_F(MouseEventTest, ReturnsCorrectCategories) {
        EXPECT_TRUE(mMousePress.isOfCategories(LZC_MOUSE, LZC_INPUT));
        EXPECT_TRUE(mMouseRelease.isOfCategories(LZC_MOUSE, LZC_INPUT));
        EXPECT_TRUE(mMouseRepeat.isOfCategories(LZC_MOUSE, LZC_INPUT));
        EXPECT_TRUE(mMouseMove.isOfCategories(LZC_MOUSE, LZC_INPUT));
        EXPECT_TRUE(mMouseScroll.isOfCategories(LZC_MOUSE, LZC_INPUT));
    }

    TEST_F(MouseEventTest, ReturnsCorrectInfo) {
        EXPECT_TRUE(mMousePress.mButton == LZ_MOUSE_LEFT && mMousePress.mAction == LZ_BUTTON_PRESS);
        EXPECT_TRUE(mMouseRelease.mButton == LZ_MOUSE_RIGHT && mMouseRelease.mAction == LZ_BUTTON_RELEASE);
        EXPECT_TRUE(mMouseRepeat.mButton == LZ_MOUSE_MID && mMouseRepeat.mAction == LZ_BUTTON_REPEAT);

        EXPECT_TRUE(mMouseMove.mX == .0f && mMouseMove.mY == .0f);
        EXPECT_TRUE(mMouseScroll.mOffset == 1.0f);
    }
};