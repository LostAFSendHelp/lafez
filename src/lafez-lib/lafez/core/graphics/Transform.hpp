#pragma once
#include <glm/glm.hpp>
#include <lafezlib_export.h>

namespace Lafez {
	struct LAFEZLIB Transform {
		Transform() noexcept;
		Transform(const Transform& other) = default;
		Transform(Transform&& other) = default;
		~Transform() = default;

		Transform& operator = (const Transform& other) = default;
		Transform& operator = (Transform&& other) = default;

		// TODO: consider separating into initial and accumulative transformations
		void rotate(float radians, const glm::vec3& axis) const;
		void translate(const glm::vec3& translation) const;
		void scale(float factor) const;

		mutable glm::mat4 rotation;
		mutable glm::mat4 translation;
		mutable float scaleFactor;
	};
};