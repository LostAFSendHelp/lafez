#include <lafez/platform_headers/lafez_gl.hpp>
#include <lafez/utils/Log.hpp>
#include <lafez/misc/lafez_exception.hpp>
#include "GlShader.hpp"
#include "GlGfx.hpp"

namespace Lafez {
	GlShader::GlShader(
		const LzString& name,
		const LzString& vSource,
		const LzString& pSource
	) :
		Bindable(LZ_BIND_TYPE_SHADER, -1),
		name(name),
		shaderId(0u)
	{
		auto vShader = createShader(GL_VERTEX_SHADER, vSource);
		auto pShader = createShader(GL_FRAGMENT_SHADER, pSource);

		shaderId = glCreateProgram();
		glAttachShader(shaderId, vShader);
		glAttachShader(shaderId, pShader);
		glLinkProgram(shaderId);

		int status;
		int length;
		char* log = nullptr;
		glGetProgramiv(shaderId, GL_LINK_STATUS, &status);

		if (!status) {
			glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &length);
			log = new char[length];
			glGetProgramInfoLog(shaderId, length * sizeof(char), NULL, log);
			auto message = fmt::format("PROGRAM LINK ERROR: {0}", log);
			delete[] log;
			LZ_RUNTIME_GUARD(false, message.c_str());
		}

		glDetachShader(shaderId, vShader);
		glDetachShader(shaderId, pShader);
		glDeleteShader(vShader);
		glDeleteShader(pShader);

		LZ_GLCALL(
			auto modelIndex = glGetUniformBlockIndex(shaderId, "u_model");
			glUniformBlockBinding(
				shaderId,
				modelIndex,
				Gfx::MODEL_BUFFER_INDEX
			);
			auto viewIndex = glGetUniformBlockIndex(shaderId, "u_view");
			glUniformBlockBinding(
				shaderId,
				viewIndex,
				Gfx::VIEW_BUFFER_INDEX
			);
			auto projectionIndex = glGetUniformBlockIndex(shaderId, "u_projection");
			glUniformBlockBinding(
				shaderId,
				projectionIndex,
				Gfx::PROJECTION_BUFFER_INDEX
			);
		);
	}

	void GlShader::bind() {
		glUseProgram(shaderId);
	}

	uint32_t GlShader::getShaderId() const {
		return shaderId;
	}

	uint32_t GlShader::createShader(
		uint32_t type,
		const LzString& source
	) {
		auto shader = glCreateShader(type);
		auto shaderSource = source.c_str();
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		int status;
		int length;
		char* log = nullptr;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (!status) {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			log = new char[length];
			glGetShaderInfoLog(shader, length * sizeof(char), NULL, log);
			auto message = fmt::format("PROGRAM LINK ERROR: {0}", log);
			delete[] log;
			LZ_RUNTIME_GUARD(false, message.c_str());
		}

		return shader;
	}
};