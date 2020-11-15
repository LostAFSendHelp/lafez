#pragma once
#include <lafez/core/lafez_event.hpp>
#include <lafez_test_pch.hpp>

namespace Lafez {
    class ApplicationEventTest : public ::testing::Test {
    public:
        WindowCloseEvent mCloseEvent;
        WindowResizeEvent mResizeEvent;

        ApplicationEventTest():
        mCloseEvent(),
        mResizeEvent(100, 200) {

        }

        ~ApplicationEventTest() {

        }

    protected:
        void SetUp() override {

        }

        void TearDown() override {

        }
    };

    TEST_F(ApplicationEventTest, ReturnsCorrectType) {
        EXPECT_EQ(mCloseEvent.mType, LZT_WINDOW_CLOSE);
        EXPECT_EQ(mResizeEvent.mType, LZT_WINDOW_RESIZE);
    }

    TEST_F(ApplicationEventTest, ReturnsCorrectCategories) {
        EXPECT_TRUE(mCloseEvent.isOfCategories(LZC_APPLICATION));
        EXPECT_TRUE(mResizeEvent.isOfCategories(LZC_APPLICATION));
    }

    TEST_F(ApplicationEventTest, ReturnsCorrectInfo) {
        EXPECT_EQ(mResizeEvent.mWidth, 100);
        EXPECT_EQ(mResizeEvent.mHeight, 200);
    }
};