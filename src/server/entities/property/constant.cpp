#include <sanguis/server/entities/property/constant.hpp>

sanguis::server::entities::property::constant::constant()
:
	value_(
		0
	)
{}

void
sanguis::server::entities::property::constant::change(
	value_type const _add
)
{
	value_ += _add;
}

sanguis::server::entities::property::constant::value_type
sanguis::server::entities::property::constant::value() const
{
	return value_;
}
