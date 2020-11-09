#pragma once
#include <lafez/core/lafe_event.hpp>
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
        mMouseUp(LZTM(Up), 0),
        mMouseDown(LZTM(Down), 0),
        mMouseScroll(LZTM(Scroll), 0),
        mMouseMove(0, 0),
        mMouseInvalid(LZTK(Up), 0),
        mWindowResize(0, 0),
        mWindowClose(false) {
            
        }

        ~EventTest() override {

        }

        void SetUp() override {

        }

        void TearDown() override {

        }
    };

    TEST_F(EventTest, ReturnsCorrectType) {
        EXPECT_EQ(mKeyUp.getType(), LZTK(Up));
        EXPECT_EQ(mKeyDown.getType(), LZTK(Down));
        EXPECT_EQ(mKeyRepeat.getType(), LZTK(Repeat));
        EXPECT_EQ(mKeyInvalid.getType(), LZTN);
        
        EXPECT_EQ(mMouseUp.getType(), LZTM(Up));
        EXPECT_EQ(mMouseDown.getType(), LZTM(Down));
        EXPECT_EQ(mMouseScroll.getType(), LZTM(Scroll));
        EXPECT_EQ(mMouseInvalid.getType(), LZTN);

        EXPECT_EQ(mWindowClose.getType(), LZTW(Close));
        EXPECT_EQ(mWindowResize.getType(), LZTW(Resize));
    }
};