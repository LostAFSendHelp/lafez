#pragma once
#include <lafez/core/lafez_renderer.hpp>

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
            *mVal = 0;
        }

        void useShaderImpl(const Shader& shader) const override {
            *mVal = 1;
        }

        void resetShaderImpl() const override {
            *mVal = -1;
        }

        ArrayBuffer* genArrayBufferImpl(float* data, LzSizeT size) override {
            return nullptr;
        }

        void bindArrayBufferImpl(const ArrayBuffer& arrayBuffer) const override {
            *mVal = 2;
        }

        void setBufferLayoutImpl(const ArrayBuffer& buffer, const VertexBufferLayout& layout) const override {
            *mVal = 3;
        }

        void resetArrayBufferImpl() const override {
            *mVal = -2;
        }

        IndexBuffer* genIndexBufferImpl(uint32_t* indices, LzSizeT count) override {
            return nullptr;
        }

        void bindIndexBufferImpl(const IndexBuffer& indexBuffer) const override {
            *mVal = 4;
        }

        void resetIndexBufferImpl() const override {
            *mVal = -4;
        }

        void initImpl() override {
            
        }

        void terminateImpl() override {
            
        }

    private:
        int* mVal;
    };
};