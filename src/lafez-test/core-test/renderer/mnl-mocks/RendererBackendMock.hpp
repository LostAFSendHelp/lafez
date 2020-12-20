#pragma once
#include <lafez/core/lafez_renderer.hpp>

#define XAND(num, bit) num |= (1 << bit)

namespace Lafez {
    class RendererBackendMock : public RendererBackend {
    public:
        RendererBackendMock(int* val):
        mVal(val) {

        }

        ~RendererBackendMock() = default;
    
    protected:
        Shader* genShaderImpl(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) override {
            return nullptr;
        }

        void deleteShaderImpl(const Shader& shader) const override {
            XAND(*mVal, 0);
        }

        void useShaderImpl(const Shader& shader) const override {
            XAND(*mVal, 1);
        }

        void resetShaderImpl() const override {
            XAND(*mVal, 2);
        }

        ArrayBuffer* genArrayBufferImpl(float* data, LzSizeT size) override {
            return nullptr;
        }

        void bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const override {
            XAND(*mVal, 3);
        }

        void setBufferLayoutImpl(const ArrayBuffer& buffer, const VertexBufferLayout& layout) const override {
            XAND(*mVal, 4);
        }

        void resetArrayBufferImpl() const override {
            XAND(*mVal, 5);
        }

        IndexBuffer* genIndexBufferImpl(uint32_t* indices, LzSizeT count) override {
            return nullptr;
        }

        void bindIndexBufferImpl(const IndexBuffer& indexBuffer) const override {
            XAND(*mVal, 6);
        }

        void resetIndexBufferImpl() const override {
            XAND(*mVal, 7);
        }

        VertexArray* genVertexArrayImpl() override {
            return nullptr;
        }

        void bindVertexArrayImpl(const VertexArray& vertexArray) const override {
            XAND(*mVal, 8);
        }

        void unbindVertexArrayImpl(const VertexArray& vertexArray) const override {
            XAND(*mVal, 9);
        }

        void resetVertexArrayImpl() const override {
            XAND(*mVal, 10);
        }

        void initImpl() override {
            
        }

        void terminateImpl() override {
            
        }

    private:
        int* mVal;
    };
};