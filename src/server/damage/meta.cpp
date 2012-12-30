#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit.hpp>


sanguis::server::damage::meta::meta(
	sanguis::server::damage::type const _type,
	sanguis::server::damage::unit const _value
)
:
	type_(
		_type
	),
	value_(
		_value
	)
{
}

sanguis::server::damage::type
sanguis::server::damage::meta::type() const
{
	return type_;
}

sanguis::server::damage::unit
sanguis::server::damage::meta::value() const
{
	return value_;
}
