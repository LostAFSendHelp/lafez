#include "RuntimeException.hpp"
#include <sstream>

namespace Lafez {
	RuntimeException::RuntimeException(
		int line,
		const char* file,
		const char* message
	) noexcept:
		Exception(line, file),
		message(message)
	{

	}

	const char* RuntimeException::what() const noexcept {
		if (buffer.empty()) {
			std::ostringstream oss{ Exception::what(), std::ios::ate };
			oss << message;
			buffer = oss.str();
		}

		return buffer.c_str();
	}

	const char* RuntimeException::getType() const noexcept {
		return "LZ_RUNTIME_EXCEPTION";
	}
};