#include "meta.hpp"

sanguis::server::damage::meta::meta(
	damage_type::type const e,
	value_type const d)
:
	e(e),
	d(d)
{}

sanguis::damage_type::type
sanguis::server::damage::meta::type() const
{
	return e;
}

sanguis::server::damage::value_type
sanguis::server::damage::meta::value() const
{
	return d;
}
