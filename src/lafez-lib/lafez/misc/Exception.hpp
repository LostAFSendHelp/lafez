#pragma once
#include <exception>
#include <lafez/lafez_pch.hpp>

namespace Lafez {
	class Exception : std::exception {
	public:
		const int mLine;
		const char* const mFile;

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
		mutable LzString mBuffer;

	private:
	};
};