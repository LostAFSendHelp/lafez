#pragma once
#include <lafez/core/lafe_event.hpp>
#include <lafez/utils/Log.hpp>
#include <lafez_test_pch.hpp>

#define LZK(x) ::Lafez::EventType::Key##x
#define LZM(x) ::Lafez::EventType::Mouse##x
#define LZW(x) ::Lafez::EventType::Window##x
#define LZN    ::Lafez::EventType::None

namespace Lafez {
    class EventTest : public ::testing::Test {
    protected:
        ::Lafez::KeyEvent mKeyUp, mKeyDown, mKeyRepeat, mKeyInvalid;
        ::Lafez::MouseButtonEvent mMouseUp, mMouseDown, mMouseScroll, mMouseInvalid;
        ::Lafez::MouseMoveEvent mMouseMove;
        ::Lafez::WindowCloseEvent mWindowClose;
        ::Lafez::WindowResizeEvent mWindowResize;

        EventTest():
        mKeyUp(LZK(Up), 0),
        mKeyDown(LZK(Down), 0),
        mKeyRepeat(LZK(Repeat), 0),
        mKeyInvalid(LZM(Up), 0),
        mMouseUp(LZM(Up), 0),
        mMouseDown(LZM(Down), 0),
        mMouseScroll(LZM(Scroll), 0),
        mMouseMove(0, 0),
        mMouseInvalid(LZK(Up), 0),
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
        EXPECT_EQ(mKeyUp.getType(), LZK(Up));
        EXPECT_EQ(mKeyDown.getType(), LZK(Down));
        EXPECT_EQ(mKeyRepeat.getType(), LZK(Repeat));
        EXPECT_EQ(mKeyInvalid.getType(), LZN);
        
        EXPECT_EQ(mMouseUp.getType(), LZM(Up));
        EXPECT_EQ(mMouseDown.getType(), LZM(Down));
        EXPECT_EQ(mMouseScroll.getType(), LZM(Scroll));
        EXPECT_EQ(mMouseInvalid.getType(), LZN);

        EXPECT_EQ(mWindowClose.getType(), LZW(Close));
        EXPECT_EQ(mWindowResize.getType(), LZW(Resize));
    }
};