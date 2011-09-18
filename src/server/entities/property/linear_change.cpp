#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/entities/property/base.hpp>

void
sanguis::server::entities::property::linear_change(
	base &_base,
	value const &_value
)
{
	base::linear_type linear_value(
		_base.linear()
	);

	linear_value.change(
		_value
	);

	_base.linear(
		linear_value
	);
}
