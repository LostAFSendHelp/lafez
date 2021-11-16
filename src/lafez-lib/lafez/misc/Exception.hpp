#pragma once
#include <exception>
#include <lafez/lafez_pch.hpp>
#include <lafezlib_export.h>

/**
 * @brief throw Lafez-styled exception, which automatically passes LINE and FILE params.
 * In order for the exception to be thrown, its constructor must receive LINE and FILE as
 * 1st and 2nd arguments.
 * 
 * @param Exception the exception type
 * @param __VA_ARGS__ constructor params after LINE and FILE
 */
#define LZ_THROW(Exception, ...) throw Exception(__LINE__, __FILE__, __VA_ARGS__)

namespace Lafez {
	class LAFEZLIB Exception : public std::exception {
	public:
		const int line;
		const char* const file;

		Exception(int line, const char* file) noexcept;
		Exception(const Exception& other) = delete;
		Exception(Exception&& other) = delete;
		virtual ~Exception() = default;

		Exception& operator=(const Exception& other) = delete;
		Exception& operator=(Exception&& other) = delete;

		const char* what() const noexcept override;
		LzString getOriginString() const noexcept;
		virtual const char* getType() const noexcept;

	protected:
		mutable LzString buffer;

	private:
	};
};