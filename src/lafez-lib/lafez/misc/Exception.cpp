#include "Exception.hpp"
#include <sstream>
#include <lafez/utils/Log.hpp>

namespace Lafez {
	Exception::Exception(int line, const char* file) noexcept :
		mLine(line),
		mFile(file),
		mBuffer() {
		
	}

	const char* Exception::what() const noexcept {
		if (mBuffer.empty()) {
			std::ostringstream oss;
			oss << getType() << std::endl
				<< getOriginString() << std::endl;
			
			mBuffer = oss.str();
		}

		return mBuffer.c_str();
	}

	LzString Exception::getOriginString() const noexcept {
		std::ostringstream oss;
		oss << "[LINE] : " << mLine << std::endl
			<< "[FILE] : " << mFile;

		return oss.str();
	}

	const char* Exception::getType() const noexcept {
		return "LZ_EXCEPTION";
	}
};