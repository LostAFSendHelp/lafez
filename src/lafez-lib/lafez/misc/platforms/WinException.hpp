#pragma once
#ifdef __LZ_WIN

#include <lafez/misc/Exception.hpp>
#include <Windows.h>

namespace Lafez {
	class LAFEZLIB WinException : public Exception {
	public:
		const HRESULT mResult;

		WinException(int line, const char* file, HRESULT result) noexcept;
		WinException(const WinException& other) = delete;
		WinException(WinException&& other) = delete;

		WinException& operator=(const WinException& other) = delete;
		WinException& operator=(WinException&& other) = delete;

		~WinException() = default;

		const char* what() const noexcept override;
		const char* getType() const noexcept override;

		static LzString translateErrorCode(HRESULT result) noexcept;

	private:

	};
};

#define LZ_WINEXCEPT(x) Lafez::WinException(__LINE__, __FILE__, x)
#define LZ_WINEXCEPT_LAST Lafez::WinException(__LINE__, __FILE__, GetLastError())

#endif