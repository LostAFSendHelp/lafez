#include "BadFileException.hpp"
#include <sstream>

namespace Lafez {
	BadFileException::BadFileException(
		int line,
		const char* file,
		const char* path,
		const char* message
	) noexcept : Exception(line, file),
		mPath(path),
		mMessage(message) {

	}

	const char* BadFileException::what() const noexcept {
		if (mBuffer.empty()) {
			std::ostringstream oss{ Exception::what(), std::ios::ate };
			oss << "[FILE AT PATH] : " << mPath << std::endl
				<< "[INFO]		   : " << mMessage;
			mBuffer = oss.str();
		}

		return mBuffer.c_str();
	}

	const char* BadFileException::getType() const noexcept {
		return "LZ_BAD_FILE_EXCEPTION";
	}
}