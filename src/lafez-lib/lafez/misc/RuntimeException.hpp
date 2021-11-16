#pragma once
#include "Exception.hpp"

namespace Lafez {
	class LAFEZLIB RuntimeException final : public Exception {
	public:
		const char* message;

		RuntimeException(int line, const char* file, const char* message) noexcept;
		RuntimeException(const RuntimeException& other) = delete;
		RuntimeException(RuntimeException&& other) = delete;
		~RuntimeException() = default;

		RuntimeException& operator=(const RuntimeException& other) = delete;
		RuntimeException& operator=(RuntimeException&& other) = delete;

		const char* what() const noexcept override;
		const char* getType() const noexcept override;

	private:
	};
};