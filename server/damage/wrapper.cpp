#include "wrapper.hpp"
#include "meta.hpp"

sanguis::server::damage::wrapper::wrapper(
	damage_type::type const e
)
:
	e(e)
{}

sanguis::server::damage::meta const
sanguis::server::damage::wrapper::operator=(
	unit const c
) const
{
	return meta(
		e,
		c
	);
}
