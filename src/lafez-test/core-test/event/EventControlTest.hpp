#pragma once
#include <lafez/core/lafez_event.hpp>
#include <lafez_test_pch.hpp>

namespace Lafez {
    class EventControlTest : public ::testing::Test {
    public:
        DisposeBag mDisposeBagAll, mDisposeBagPartial;
        EventCenter mEventCenter;
        uint8_t mVal1, mVal2, mVal3;

        EventControlTest():
        mDisposeBagAll(),
        mDisposeBagPartial(),
        mEventCenter(),
        mVal1(0), mVal2(0), mVal3(0) {

        }

        ~EventControlTest() {

        }

    protected:
        void SetUp() override {
            auto sub1 = mEventCenter.subscribe([&](Event& event) {
                if (event.mType == LZT_KEY) {
                    ++mVal1;
                }
            });

            auto sub2 = mEventCenter.subscribe([&](Event& event) {
                ++mVal2;
            });

            auto sub3 = mEventCenter.subscribe([&](Event& event) {
                if (event.mType == LZT_WINDOW_CLOSE) {
                    ++mVal3;
                    event.handle();
                }
            });

            auto sub4 = mEventCenter.subscribe([&](Event& event) {
                mVal3 += 2;
            });

            mDisposeBagAll.dispose(sub1);
            mDisposeBagAll.dispose(sub2);
            mDisposeBagAll.dispose(sub3);
            mDisposeBagAll.dispose(sub4);

            mDisposeBagPartial.dispose(sub1);
            mDisposeBagPartial.dispose(sub2);
        }

        void TearDown() override {
            mVal1 = mVal2 = mVal3 = 0;
            mDisposeBagAll.dump();
            mDisposeBagPartial.dump();
            mEventCenter.flush();
        }
    };

    TEST_F(EventControlTest, ReturnsCorrectCounts) {
        EXPECT_EQ(mEventCenter.subscriptionCount(), 4);
        EXPECT_EQ(mDisposeBagAll.subscriptionCount(), 4);
        EXPECT_EQ(mDisposeBagPartial.subscriptionCount(), 2);
    }

    TEST_F(EventControlTest, HandlesEventCorrectly) {
        auto e1 = KeyEvent(0, LZ_BUTTON_PRESS);
        mEventCenter.emit(e1);
        EXPECT_EQ(mVal1, 1);
        EXPECT_EQ(mVal2, 1);
        EXPECT_EQ(mVal3, 2);

        auto e2 = WindowCloseEvent();
        mEventCenter.emit(e2);
        EXPECT_EQ(mVal1, 1);
        EXPECT_EQ(mVal2, 2);
        EXPECT_EQ(mVal3, 3);
    }

    TEST_F(EventControlTest, DoesNotDispatchDeadSubscriptionsCaseAll) {
        auto e1 = KeyEvent(0, LZ_BUTTON_RELEASE);
        mEventCenter.emit(e1);
        EXPECT_EQ(mVal1, 1);
        EXPECT_EQ(mVal2, 1);
        EXPECT_EQ(mVal3, 2);

        mDisposeBagAll.dump();
        EXPECT_EQ(mDisposeBagAll.subscriptionCount(), 0);
        EXPECT_EQ(mEventCenter.subscriptionCount(), 4);

        mEventCenter.emit(e1);
        EXPECT_EQ(mVal1, 1);
        EXPECT_EQ(mVal2, 1);
        EXPECT_EQ(mVal3, 2);
    }

    TEST_F(EventControlTest, DoesNotDispatchDeadSubscriptionsCasePartial) {
        auto e1 = KeyEvent(0, LZ_BUTTON_RELEASE);
        mEventCenter.emit(e1);
        EXPECT_EQ(mVal1, 1);
        EXPECT_EQ(mVal2, 1);
        EXPECT_EQ(mVal3, 2);

        mDisposeBagPartial.dump();
        EXPECT_EQ(mDisposeBagPartial.subscriptionCount(), 0);
        EXPECT_EQ(mEventCenter.subscriptionCount(), 4);

        mEventCenter.emit(e1);
        EXPECT_EQ(mEventCenter.subscriptionCount(), 2);
        EXPECT_EQ(mVal1, 1);
        EXPECT_EQ(mVal2, 1);
        EXPECT_EQ(mVal3, 4);
    }
};