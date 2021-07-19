#pragma once
#include "Exception.hpp"

namespace Lafez {
	class LAFEZLIB BadFileException : public Exception {
	public:
		const char* const mPath;
		const char* const mMessage;

		BadFileException(int line, const char* file, const char* path, const char* message) noexcept;
		BadFileException(const BadFileException& other) = delete;
		BadFileException(BadFileException&& other) = delete;
		~BadFileException() = default;

		BadFileException& operator=(const BadFileException& other) = delete;
		BadFileException&& operator=(BadFileException&& other) = delete;

		const char* what() const noexcept override;
		const char* getType() const noexcept override;

	private:
	};
};