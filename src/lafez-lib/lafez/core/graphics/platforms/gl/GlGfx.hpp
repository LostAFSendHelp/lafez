#pragma once
#include <lafez/core/graphics/Gfx.hpp>
#include <lafez/platform_headers/lafez_gl.hpp>

namespace Lafez {
	class GlGfx final : public Gfx {
	public:
		GlGfx(GLFWwindow* windowPtr);
		~GlGfx();

		GlGfx(const GlGfx& other) = delete;
		GlGfx(GlGfx&& other) = delete;
		GlGfx& operator=(const GlGfx& other) = delete;
		GlGfx& operator=(GlGfx&& other) = delete;

		void clearBuffer(float r, float g, float b, float a) override;
		void setViewport(float x, float y, float width, float height) override;
		void swapBuffers() override;
		void drawList(unsigned int vertices) override;
		void drawIndexed(unsigned int indices) override;
		Bindable* genShader(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) override;
		Bindable* genVertexBuffer(float* data, LzSizeT dataSize, LzSizeT vertexCount) override;
		Bindable* genIndexBuffer(uint32_t* indices, LzSizeT indexCount) override;
		Bindable* genVBLayout(VertexAttribute* attributes, LzSizeT attribCount, const Bindable* shader) override;
		Bindable* genDefaultShader() override;

	private:
		GLFWwindow* windowPtr;
	};
};