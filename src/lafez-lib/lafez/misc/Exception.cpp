#include "Exception.hpp"
#include <sstream>
#include <lafez/utils/Log.hpp>

namespace Lafez {
	Exception::Exception(int line, const char* file) noexcept :
		line(line),
		file(file),
		buffer() {
		
	}

	const char* Exception::what() const noexcept {
		if (buffer.empty()) {
			std::ostringstream oss;
			oss << getType() << std::endl
				<< getOriginString() << std::endl;
			
			buffer = oss.str();
		}

		return buffer.c_str();
	}

	LzString Exception::getOriginString() const noexcept {
		std::ostringstream oss;
		oss << "[LINE] : " << line << std::endl
			<< "[FILE] : " << file;

		return oss.str();
	}

	const char* Exception::getType() const noexcept {
		return "LZ_EXCEPTION";
	}
};