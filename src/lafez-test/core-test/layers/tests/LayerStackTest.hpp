#pragma once
#include <lafez_test_pch.hpp>
#include <lafez/core/lafez_event.hpp>
#include <core-test/layers/mnl-mocks/ConsumingLayer.hpp>
#include <core-test/layers/mnl-mocks/NonConsumingLayer.hpp>

namespace Lafez {
    class LayerStackTest : public ::testing::Test {
    public:
        LayerStack                      mStack;
        LzShrPtr<Layer>                 mCL1, mCL2, mCL3;
        LzShrPtr<Layer>                 mNCL1, mNCL2, mNCL3;
        LzShrPtr<ConsumingLayer>        mCLP1, mCLP2, mCLP3;
        LzShrPtr<NonConsumingLayer>     mNCLP1, mNCLP2, mNCLP3;

        LayerStackTest():
        mStack(),
        mCL1(Layer::create<ConsumingLayer>("mCL1")),
        mCL2(Layer::create<ConsumingLayer>("mCL2")),
        mCL3(Layer::create<ConsumingLayer>("mCL3")),
        mNCL1(Layer::create<NonConsumingLayer>("mNCL1")),
        mNCL2(Layer::create<NonConsumingLayer>("mNCL2")),
        mNCL3(Layer::create<NonConsumingLayer>("mNCL3")),
        mCLP1(std::static_pointer_cast<ConsumingLayer>(mCL1)),
        mCLP2(std::static_pointer_cast<ConsumingLayer>(mCL2)),
        mCLP3(std::static_pointer_cast<ConsumingLayer>(mCL3)),
        mNCLP1(std::static_pointer_cast<NonConsumingLayer>(mNCL1)),
        mNCLP2(std::static_pointer_cast<NonConsumingLayer>(mNCL2)),
        mNCLP3(std::static_pointer_cast<NonConsumingLayer>(mNCL3)) {

        }

        ~LayerStackTest() {

        }

    protected:
        void SetUp() override {

        }

        void TearDown() override {
            mStack.flush();
            mCLP1->mWasFedEvent = false;
            mCLP2->mWasFedEvent = false;
            mCLP3->mWasFedEvent = false;
            mNCLP1->mWasFedEvent = false;
            mNCLP2->mWasFedEvent = false;
            mNCLP3->mWasFedEvent = false;
        }

    private:

    };

    TEST_F(LayerStackTest, ShouldCallOnAttach) {
        mStack.pushLayer(mCL1);
        EXPECT_TRUE(mCLP1->mAttached);

        mStack.popLayer();
        EXPECT_FALSE(mCLP1->mAttached);
    }

    TEST_F(LayerStackTest, ShouldRemoveLayersCorrectly) {
        // Should pop nothing
        EXPECT_EQ(mStack.popLayer(), nullptr);

        mStack.pushLayers(mCL1, mCL2, mCL3, mNCL1, mNCL2, mNCL3);
        
        // Should remove mNCL3
        EXPECT_EQ(mStack.popLayer()->mTag, "mNCL3");
        
        // Should remove mCL1
        EXPECT_EQ(mStack.removeById(mCL1->mID)->mID, mCLP1->mID);
        
        // Resulting vector should not be empty
        EXPECT_EQ(mStack.removeByTag("mCL2").front()->mID, mCL2->mID);
        
        // Should return empty vector as mCL2 already removed
        EXPECT_EQ(mStack.removeByTag("mCL2").size(), 0);
    }

    TEST_F(LayerStackTest, ShouldPropagateEventCorrectly) {
        mStack.pushLayers(mNCL1, mCL1, mNCL2);
        KeyEvent e{ 81, LZ_BUTTON_PRESS };
        mStack.onEvent(e);

        EXPECT_TRUE(mNCLP2->mWasFedEvent);
        EXPECT_TRUE(mCLP1->mWasFedEvent);
        EXPECT_FALSE(mNCLP1->mWasFedEvent);
    }

    TEST_F(LayerStackTest, ShouldNotPropagateToRemovedLayers) {
        mStack.pushLayers(mNCL1, mCL1, mNCL2);
        KeyEvent e1{ 81, LZ_BUTTON_PRESS };
        mStack.removeByTag("mNCL2");
        mStack.onEvent(e1);

        EXPECT_FALSE(mNCLP2->mWasFedEvent);
        EXPECT_TRUE(mCLP1->mWasFedEvent);
        EXPECT_FALSE(mNCLP1->mWasFedEvent);

        mStack.removeById(mCL1->mID);
        KeyEvent e2{ 81, LZ_BUTTON_PRESS };
        mStack.onEvent(e2);

        EXPECT_TRUE(mNCLP1->mWasFedEvent);
    }
};