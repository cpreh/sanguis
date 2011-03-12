#include "meta.hpp"

sanguis::server::damage::meta::meta(
	damage_type::type const _type,
	unit const _value
)
:
	type_(_type),
	value_(_value)
{}

sanguis::damage_type::type
sanguis::server::damage::meta::type() const
{
	return type_;
}

sanguis::server::damage::unit
sanguis::server::damage::meta::value() const
{
	return value_;
}
