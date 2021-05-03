#ifdef __LZ_WIN

#include "WinException.hpp"
#include <sstream>
#include <iomanip>

namespace Lafez {
	WinException::WinException(int line, const char* file, HRESULT result) noexcept:
		Exception(line, file),
		mResult(result) {

	}

	const char* WinException::what() const noexcept {
		if (mBuffer.empty()) {
			std::ostringstream oss;
			oss << getType() << std::endl
				<< "[ERROR CODE] : " << std::uppercase << std::hex << mResult << std::endl
				<< "[DESCRIPTION] : " << translateErrorCode(mResult) << std::endl
				<< getOriginString() << std::endl;
			
			mBuffer = oss.str();
		}

		return mBuffer.c_str();
	}

	const char* WinException::getType() const noexcept {
		return "[LZ_WINDOW_EXCEPTION]";
	}

	LzString WinException::translateErrorCode(HRESULT result) noexcept {
		char* buffer = nullptr;
		auto length = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr,
			result,
			0,
			reinterpret_cast<LPSTR>(&buffer),
			0,
			nullptr
		);

		if (length <= 0) {
			return "UNIDENTIFIED ERROR CODE";
		}

		LzString errorString = buffer;
		LocalFree(buffer);
		return errorString;
	}
};

#endif