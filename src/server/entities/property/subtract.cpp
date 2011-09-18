#include <sanguis/server/entities/property/subtract.hpp>
#include <sanguis/server/entities/property/changeable.hpp>

void
sanguis::server::entities::property::subtract(
	changeable &_changeable,
	value const &_value
)
{
	_changeable.current(
		_changeable.current()
		- _value
	);
}
