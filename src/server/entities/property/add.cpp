#include <sanguis/server/entities/property/add.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

void
sanguis::server::entities::property::add(
	changeable &_changeable,
	value const &_value
)
{
	_changeable.current(
		std::min(
			_changeable.max(),
			_changeable.current()
			+ _value
		)
	);
}
