#include "constant.hpp"

sanguis::server::entities::property::constant::constant()
:
	value_(
		0
	)
{}

void
sanguis::server::entities::property::constant::add(
	value_type const add_
)
{
	value_ += add_;
}

void
sanguis::server::entities::property::constant::remove(
	value_type const sub_
)
{
	value_ -= sub_;
}

sanguis::server::entities::property::constant::value_type
sanguis::server::entities::property::constant::value() const
{
	return value_;
}
