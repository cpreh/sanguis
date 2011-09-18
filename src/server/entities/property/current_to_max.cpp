#include <sanguis/server/entities/property/current_to_max.hpp>
#include <sanguis/server/entities/property/changeable.hpp>

void
sanguis::server::entities::property::current_to_max(
	changeable &_changeable
)
{
	_changeable.current(
		_changeable.max()
	);
}
