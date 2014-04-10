#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/constant.hpp>
#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/entities/property/value.hpp>


void
sanguis::server::entities::property::constant_change(
	sanguis::server::entities::property::base &_base,
	sanguis::server::entities::property::value const &_value
)
{
	sanguis::server::entities::property::constant constant_value(
		_base.constant()
	);

	constant_value.change(
		_value
	);

	_base.constant(
		constant_value
	);
}
