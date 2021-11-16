#include "platforms/GlException.hpp"
#include "RuntimeException.hpp"
#include "Exception.hpp"

#ifdef __LZ_WIN
#include "platforms/WinException.hpp"

#define LZ_WINEXCEPT(x) Lafez::WinException(__LINE__, __FILE__, x)
#define LZ_WINEXCEPT_LAST Lafez::WinException(__LINE__, __FILE__, GetLastError())
#endif

#define LZ_RUNTIME_GUARD(statement, ...)\
if (!statement) {\
	throw Lafez::RuntimeException(__LINE__, __FILE__, __VA_ARGS__);\
}
