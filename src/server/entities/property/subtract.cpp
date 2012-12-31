#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/subtract.hpp>
#include <sanguis/server/entities/property/value.hpp>


void
sanguis::server::entities::property::subtract(
	sanguis::server::entities::property::changeable &_changeable,
	sanguis::server::entities::property::value const &_value
)
{
	_changeable.current(
		_changeable.current()
		- _value
	);
}
