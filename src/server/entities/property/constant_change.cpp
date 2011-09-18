#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/entities/property/base.hpp>

void
sanguis::server::entities::property::constant_change(
	property::base &_base,
	property::value const &_value
)
{
	base::constant_type constant_value(
		_base.constant()
	);

	constant_value.change(
		_value
	);

	_base.constant(
		constant_value
	);
}
