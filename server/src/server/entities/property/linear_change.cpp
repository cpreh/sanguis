#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/linear.hpp>
#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/entities/property/value.hpp>


void
sanguis::server::entities::property::linear_change(
	sanguis::server::entities::property::base &_base,
	sanguis::server::entities::property::value const &_value
)
{
	sanguis::server::entities::property::linear linear_value(
		_base.linear()
	);

	linear_value.change(
		_value
	);

	_base.linear(
		linear_value
	);
}
