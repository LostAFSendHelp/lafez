#pragma once
#include "Bindable.hpp"
#include "VertexAttribute.hpp"
#include <lafez/misc/RuntimeException.hpp>


namespace Lafez {
	class LAFEZLIB Gfx {
	public:
		Gfx(const Gfx& other) = delete;
		Gfx(Gfx&& other) = delete;
		Gfx& operator=(const Gfx& other) = delete;
		Gfx& operator=(Gfx&& other) = delete;

		static Gfx* gfx();
		
		virtual void clearBuffer(float r, float g, float b, float a) = 0;
		virtual void setViewport(float x, float y, float width, float height) = 0;
		virtual void swapBuffers() = 0;
		virtual void drawList(unsigned int vertices) = 0;
		virtual void drawIndexed(unsigned int indices) = 0;
		virtual Bindable* genShader(const LzString& name, const LzString& vSource, const LzString& fSource, bool retain = false) = 0;
		virtual Bindable* genVertexBuffer(float* data, LzSizeT dataSize, LzSizeT vertexCount) = 0;
		virtual Bindable* genIndexBuffer(uint32_t* indices, LzSizeT indexCount) = 0;
		virtual Bindable* genVBLayout(VertexAttribute* attributes, LzSizeT attribCount, const Bindable* shader) = 0;
		virtual Bindable* genDefaultShader() = 0;

		template<typename T, typename ... Args>
		static void startUp(Args&& ... args);
		static void shutDown();

	protected:
		Gfx() noexcept = default;
		virtual ~Gfx() noexcept = default;

	private:
		static Gfx* shared;
	};

	template<typename T, typename ... Args>
	void Gfx::startUp(Args&& ... args) {
		if (shared) {
			throw Lafez::RuntimeException(__LINE__, __FILE__, "INVALID ATTEMPT TO RE-STARTUP NON-NULL RENDERER BACKEND INSTANCE");
		}

		Gfx::shared = new T{ std::forward<Args>(args)... };
	}
};