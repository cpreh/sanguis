#include "wrapper.hpp"
#include "meta.hpp"

sanguis::server::damage::wrapper::wrapper(
	damage_type::type const _type
)
:
	type_(_type)
{}

sanguis::server::damage::meta const
sanguis::server::damage::wrapper::operator=(
	unit const _unit
) const
{
	return
		meta(
			type_,
			_unit
		);
}
