#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/wrapper.hpp>


sanguis::server::damage::wrapper::wrapper(
	sanguis::server::damage::type const _type
)
:
	type_(
		_type
	)
{
}

sanguis::server::damage::meta const
sanguis::server::damage::wrapper::operator=(
	sanguis::server::damage::unit const _unit
) const
{
	return
		sanguis::server::damage::meta(
			type_,
			_unit
		);
}
