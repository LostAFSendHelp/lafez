#pragma once
#include <lafez/platform_headers/lafez_gl.hpp>
#include <lafez/misc/Exception.hpp>

namespace Lafez {
	class GlException : public Exception {
	public:
		GlException(int line, const char* file, const GLenum* glError, LzSizeT errorCount) noexcept;
		GlException(const GlException& other) = delete;
		GlException(GlException&& other) = delete;
		~GlException() = default;

		GlException& operator = (const GlException& other) = delete;
		GlException& operator = (GlException&& other) = delete;

		const char* what() const noexcept override;
		const char* getType() const noexcept override;

		static LzString translateErrorCode(GLenum glError) noexcept;
		static LzVec<GLenum> getAllErrors() noexcept;

	private:
		mutable bool firstWhatCalled;
	};
};

#define LZ_GLCALL(statements)\
	statements\
	auto errors = Lafez::GlException::getAllErrors();\
	if (!errors.empty()) {\
		throw Lafez::GlException(__LINE__, __FILE__, &errors[0], errors.size());\
	}