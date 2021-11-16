#include <lafez/platform_headers/lafez_gl.hpp>
#include "GlException.hpp"
#include <sstream>

namespace Lafez {
	GlException::GlException(
		int line,
		const char* file,
		const GLenum* glError,
		LzSizeT errorCount
	) noexcept :
		Exception(line, file),
		firstWhatCalled(false)
	{
		std::ostringstream oss;

		for (auto index = 0; index < errorCount; ++index) {
			oss << std::endl
				<< "[ERROR CODE #" << index << "] : " << glError[index] << std::endl
				<< "[DESCRIPTION] : " << translateErrorCode(glError[index]) << std::endl
				<< getOriginString() << std::endl;
		}

		buffer = oss.str();
	}

	const char* GlException::what() const noexcept {
		if (!firstWhatCalled) {
			buffer = getType() + buffer;
			firstWhatCalled = true;
		}

		return buffer.c_str();
	}

	const char* GlException::getType() const noexcept {
		return "[LZ_OPENGL_EXCEPTION]";
	}

	LzString GlException::translateErrorCode(GLenum glError) noexcept {
		switch (glError)
		{
		case GL_INVALID_ENUM:					return "Invalid enum";
		case GL_INVALID_VALUE:					return "Invalid value";
		case GL_INVALID_OPERATION:				return "Invalid operation";
		case GL_STACK_OVERFLOW:					return "Stack overflow";
		case GL_STACK_UNDERFLOW:				return "Stack underflow";
		case GL_OUT_OF_MEMORY:					return "Out of memory";
		case GL_INVALID_FRAMEBUFFER_OPERATION:	return "Framebuffer operation";
		default:								return "Unknown";
		}
	}

	LzVec<GLenum> GlException::getAllErrors() noexcept {
		LzVec<GLenum> errors;
		auto error = glGetError();

		while (error) {
			errors.push_back(error);
			error = glGetError();
		}

		return errors;
	}
};