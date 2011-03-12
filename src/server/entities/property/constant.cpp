#include "constant.hpp"

sanguis::server::entities::property::constant::constant()
:
	value_(
		0
	)
{}

void
sanguis::server::entities::property::constant::change(
	value_type const add_
)
{
	value_ += add_;
}

sanguis::server::entities::property::constant::value_type
sanguis::server::entities::property::constant::value() const
{
	return value_;
}
