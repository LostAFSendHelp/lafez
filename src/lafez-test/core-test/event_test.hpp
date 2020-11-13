#pragma once
#include <lafez/core/lafez_event.hpp>
#include <lafez/utils/Log.hpp>
#include <lafez_test_pch.hpp>

#define LZTK(x) ::Lafez::EventType::Key##x
#define LZTM(x) ::Lafez::EventType::Mouse##x
#define LZTW(x) ::Lafez::EventType::Window##x
#define LZTN    ::Lafez::EventType::None

#define LZCK    ::Lafez::EventCategory::KeyInput
#define LZCM    ::Lafez::EventCategory::MouseInput
#define LZCI    ::Lafez::EventCategory::Input
#define LZCA    ::Lafez::EventCategory::Application
#define LZCN    ::Lafez::EventCategory::None

namespace Lafez {
    class EventTest : public ::testing::Test {
    protected:
        ::Lafez::KeyEvent mKeyUp, mKeyDown, mKeyRepeat, mKeyInvalid;
        ::Lafez::MouseButtonEvent mMouseUp, mMouseDown, mMouseScroll, mMouseInvalid;
        ::Lafez::MouseMoveEvent mMouseMove;
        ::Lafez::WindowCloseEvent mWindowClose;
        ::Lafez::WindowResizeEvent mWindowResize;

        EventTest():
        mKeyUp(LZTK(Up), 0),
        mKeyDown(LZTK(Down), 0),
        mKeyRepeat(LZTK(Repeat), 0),
        mKeyInvalid(LZTM(Up), 0),
        mMouseUp(LZTM(Up), ::Lafez::MouseButton::Left),
        mMouseDown(LZTM(Down), ::Lafez::MouseButton::Left),
        mMouseScroll(LZTM(Scroll), ::Lafez::MouseButton::Left),
        mMouseMove(0, 0),
        mMouseInvalid(LZTK(Up), ::Lafez::MouseButton::Left),
        mWindowResize(0, 0),
        mWindowClose() {
            
        }

        ~EventTest() override {

        }

        void SetUp() override {

        }

        void TearDown() override {

        }
    };

    TEST_F(EventTest, ReturnsCorrectType) {
        EXPECT_EQ(mKeyUp.mType, LZTK(Up));
        EXPECT_EQ(mKeyDown.mType, LZTK(Down));
        EXPECT_EQ(mKeyRepeat.mType, LZTK(Repeat));
        EXPECT_EQ(mKeyInvalid.mType, LZTN);
        
        EXPECT_EQ(mMouseUp.mType, LZTM(Up));
        EXPECT_EQ(mMouseDown.mType, LZTM(Down));
        EXPECT_EQ(mMouseScroll.mType, LZTM(Scroll));
        EXPECT_EQ(mMouseInvalid.mType, LZTN);

        EXPECT_EQ(mWindowClose.mType, LZTW(Close));
        EXPECT_EQ(mWindowResize.mType, LZTW(Resize));
    }

    TEST_F(EventTest, ReturnsCorrectCategories) {
        EXPECT_TRUE(mKeyUp.isOfCategories(LZCI, LZCK));
        EXPECT_TRUE(mKeyDown.isOfCategories(LZCI, LZCK));
        EXPECT_TRUE(mKeyRepeat.isOfCategories(LZCI, LZCK));
        EXPECT_TRUE(mKeyInvalid.isOfCategories(LZCN));

        EXPECT_TRUE(mMouseUp.isOfCategories(LZCI, LZCM));
        EXPECT_TRUE(mMouseDown.isOfCategories(LZCI, LZCM));
        EXPECT_TRUE(mMouseMove.isOfCategories(LZCI, LZCM));
        EXPECT_TRUE(mMouseScroll.isOfCategories(LZCI, LZCM));
        EXPECT_TRUE(mMouseInvalid.isOfCategories(LZCN));

        EXPECT_TRUE(mWindowClose.isOfCategories(LZCA));
        EXPECT_TRUE(mWindowResize.isOfCategories(LZCA));
    }
};