#pragma once
#include <lafez_test_pch.hpp>
#include <core-test/renderer/mnl-mocks/RendererBackendMock.hpp>

namespace Lafez {
    class BufferTest : public ::testing::Test {
    public:
        int mVal = 0;
        ArrayBuffer mArrayBuffer{ 0, 0 };
        IndexBuffer mIndexBuffer{ 0, 5 };

        BufferTest() = default;
        ~BufferTest() = default;

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

    TEST_F(BufferTest, BuffersShouldCallBackendFunctions) {
        EXPECT_FALSE(RendererBackend::genArrayBuffer(nullptr, 0, 0));
        EXPECT_FALSE(RendererBackend::genIndexBuffer(nullptr, 0));
        
        mArrayBuffer.bind();
        EXPECT_TRUE(mVal & (1 << 3));
        RendererBackend::resetArrayBuffer();
        EXPECT_TRUE(mVal & (1 << 5));
        RendererBackend::setBufferLayout(mArrayBuffer, { { } });
        EXPECT_TRUE(mVal & (1 << 4));
        
        mIndexBuffer.bind();
        EXPECT_TRUE(mVal & (1 << 6));
        RendererBackend::resetIndexBuffer();
        EXPECT_TRUE(mVal & (1 << 7));

        // Check index count, snuck this in here because I'm too lazy to create a separate test for it
        EXPECT_EQ(mIndexBuffer.mIndexCount, 5);
    }

    TEST_F(BufferTest, ArrayBufferShouldSetupLayoutCorrectly) {
        VertexBufferLayout layout({
            LZ_PTYPE_INT,
            LZ_PTYPE_VEC2I,
            LZ_PTYPE_VEC3I,
            LZ_PTYPE_VEC4I,
            LZ_PTYPE_FLOAT,
            LZ_PTYPE_VEC2F,
            LZ_PTYPE_VEC3F,
            LZ_PTYPE_VEC4F,
        });

        auto attribs = layout.getAttributes();
        
        for (auto i = 0; i < 8; ++i) {
            EXPECT_EQ(attribs[i].mIndex, i);
            EXPECT_EQ(attribs[i].mStride, 10 * sizeof(std::uint32_t) + 10 * sizeof(float));
        }

        EXPECT_EQ(attribs[0].mElementSize, 1);
        EXPECT_EQ(attribs[1].mElementSize, 2);
        EXPECT_EQ(attribs[2].mElementSize, 3);
        EXPECT_EQ(attribs[3].mElementSize, 4);
        EXPECT_EQ(attribs[4].mElementSize, 1);
        EXPECT_EQ(attribs[5].mElementSize, 2);
        EXPECT_EQ(attribs[6].mElementSize, 3);
        EXPECT_EQ(attribs[7].mElementSize, 4);

        EXPECT_EQ(attribs[0].mSize, 1 * sizeof(std::uint32_t));
        EXPECT_EQ(attribs[1].mSize, 2 * sizeof(std::uint32_t));
        EXPECT_EQ(attribs[2].mSize, 3 * sizeof(std::uint32_t));
        EXPECT_EQ(attribs[3].mSize, 4 * sizeof(std::uint32_t));
        EXPECT_EQ(attribs[4].mSize, 1 * sizeof(float));
        EXPECT_EQ(attribs[5].mSize, 2 * sizeof(float));
        EXPECT_EQ(attribs[6].mSize, 3 * sizeof(float));
        EXPECT_EQ(attribs[7].mSize, 4 * sizeof(float));

        EXPECT_EQ(attribs[0].mOffset, 0);
        EXPECT_EQ(attribs[1].mOffset, 1 * sizeof(std::uint32_t));
        EXPECT_EQ(attribs[2].mOffset, 3 * sizeof(std::uint32_t));
        EXPECT_EQ(attribs[3].mOffset, 6 * sizeof(std::uint32_t));
        EXPECT_EQ(attribs[4].mOffset, 10 * sizeof(std::uint32_t));

        auto tempOffset = 10 * sizeof(std::uint32_t);
        EXPECT_EQ(attribs[5].mOffset, tempOffset + 1 * sizeof(float));
        EXPECT_EQ(attribs[6].mOffset, tempOffset + 3 * sizeof(float));
        EXPECT_EQ(attribs[7].mOffset, tempOffset + 6 * sizeof(float));
    }
};