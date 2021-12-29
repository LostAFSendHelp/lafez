#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <lafez/utils/Log.hpp>

namespace Lafez {
	Transform::Transform() noexcept :
		rotation(1.0f),
		translation(1.0f),
		scaleFactor(1.0f)
	{

	}

	void Transform::rotate(float radians, const glm::vec3& axis) const {
		rotation = glm::rotate(rotation, radians, axis);
	}

	void Transform::translate(const glm::vec3& translation) const {
		this->translation = glm::translate(this->translation, translation);
	}

	void Transform::scale(float factor) const {
		LZ_ENGINE_GUARD_VOID((factor != 0), "Aborting illegal attempt to scale by 0");
		scaleFactor *= factor;
	}
};