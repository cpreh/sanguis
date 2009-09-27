#include "meta.hpp"

sanguis::server::damage::meta::meta(
	damage_type::type const e,
	unit const d
)
:
	e(e),
	d(d)
{}

sanguis::damage_type::type
sanguis::server::damage::meta::type() const
{
	return e;
}

sanguis::server::damage::unit
sanguis::server::damage::meta::value() const
{
	return d;
}
