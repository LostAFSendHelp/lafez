#include "Drawable.hpp"
#include <lafez/misc/lafez_exception.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lafez {
	uint32_t Drawable::count = 0;

	Drawable::Drawable(Gfx* const gfx): 
		id(count++),
		bindables(),
		gfx(gfx),
		indexCount(0u),
		vertexCount(0u),
		transform()
	{
		LZ_RUNTIME_GUARD(gfx, "Nullptr of type Gfx passed to Drawable object");
	}

	Drawable::~Drawable() noexcept {
		
	}

	void Drawable::draw() {
		LZ_RUNTIME_GUARD((indexCount > 0 || vertexCount > 0), "Vertex Buffer and Index Buffer missing from Drawable");
		
		for (const auto& item : bindables) {
			item->bind();
		}

		auto scale = glm::scale(glm::mat4{ 1.0f }, glm::vec3{ transform.scaleFactor });
		auto model = transform.translation * transform.rotation * scale;
		gfx->setModel(model);

		if (indexCount > 0) {
			gfx->drawIndexed(indexCount);
		} else {
			gfx->drawList(vertexCount);
		}
	}

	void Drawable::addBindable(const LzShrPtr<Bindable>& bindable) {
		LZ_RUNTIME_GUARD(bindable, "Bindable must not be NULL");

		for (const auto& item : bindables) {
			LZ_RUNTIME_GUARD((bindable->id != item->id), "Bindable already added to Drawable");
		}

		// do not bind buffer layout if vertex layout has not been added
		auto canBind = !(bindable->bindType == LZ_BIND_TYPE_LAYOUT && vertexCount == 0);
		LZ_RUNTIME_GUARD(canBind, "Vertex buffer must be added before buffer layout can be added");

		bindables.push_back(bindable);

		if (bindable->bindType == LZ_BIND_TYPE_IBUFF) {
			indexCount = bindable->customBindValue;
		} else if (bindable->bindType == LZ_BIND_TYPE_VBUFF) {
			vertexCount = bindable->customBindValue;
		}
	}
};