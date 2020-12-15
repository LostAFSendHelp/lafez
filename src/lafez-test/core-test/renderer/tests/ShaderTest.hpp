#pragma once
#include <lafez_test_pch.hpp>
#include <core-test/renderer/mnl-mocks/RendererBackendMock.hpp>

namespace Lafez {
    class ShaderTest : public ::testing::Test {
    public:
        int mVal = 0;
        Shader mShader{ 0, "" };

        ShaderTest() = default;
        ~ShaderTest() = default;

    protected:
        void SetUp() override {
            RendererBackend::startUp<RendererBackendMock>(&mVal);
            mVal = 0;
        }

        void TearDown() override {
            RendererBackend::shutDown();
            mVal = 0;
        }

    private:

    };

    TEST_F(ShaderTest, ShouldCallBackendFunctions) {
        EXPECT_FALSE(RendererBackend::genShader("", "", ""));
        mShader.use();
        EXPECT_EQ(mVal, 1);
        RendererBackend::resetShader();
        EXPECT_EQ(mVal, -1);
        RendererBackend::deleteShader(mShader);
        EXPECT_EQ(mVal, 0);
    }
};