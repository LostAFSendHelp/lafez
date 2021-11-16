#include "Bindable.hpp"

namespace Lafez {
	uint32_t Bindable::count = 0;

	Bindable::Bindable(
		BindType bindType,
		int customBindValue
	) noexcept :
		id(count++),
		bindType(bindType),
		customBindValue(customBindValue)
	{
		
	}

};