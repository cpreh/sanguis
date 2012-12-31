#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/current_to_max.hpp>


void
sanguis::server::entities::property::current_to_max(
	sanguis::server::entities::property::changeable &_changeable
)
{
	_changeable.current(
		_changeable.max()
	);
}
