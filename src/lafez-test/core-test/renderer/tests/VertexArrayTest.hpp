#pragma once
#include <lafez_test_pch.hpp>
#include <core-test/renderer/mnl-mocks/RendererBackendMock.hpp>

namespace Lafez {
    class VertexArrayTest : public ::testing::Test {
    public:
        int mVal = 0;
        Shader mShader{ 0, "" };

        VertexArrayTest() = default;
        ~VertexArrayTest() = default;

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

    TEST_F(VertexArrayTest, ShouldCallBackendFunctions) {
        EXPECT_FALSE(RendererBackend::genVertexArray());

        VertexArray vao{ 0 };
        vao.bind();
        EXPECT_TRUE(mVal & (1 << 8));
        vao.unbind();
        EXPECT_TRUE(mVal & (1 << 9));
        RendererBackend::resetVertexArray();
        EXPECT_TRUE(mVal & (1 << 10));
    }

    TEST_F(VertexArrayTest, ShouldHoldOnlyOneBuffer) {
        VertexArray vao{ 0 };
        auto arrayBuffer = ::std::make_shared<ArrayBuffer>(0);
        auto indexBuffer = ::std::make_shared<IndexBuffer>(0, 5);

        vao.addArrayBuffer(arrayBuffer);
        EXPECT_TRUE(mVal & (1 << 8));
        EXPECT_TRUE(mVal & (1 << 5));
        EXPECT_TRUE(mVal & (1 << 3));

        mVal = 0;
        vao.addIndexBuffer(indexBuffer);
        EXPECT_TRUE(mVal & (1 << 8));
        EXPECT_TRUE(mVal & (1 << 7));
        EXPECT_TRUE(mVal & (1 << 6));
    }
};