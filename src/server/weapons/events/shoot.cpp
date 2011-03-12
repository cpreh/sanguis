#include "shoot.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::weapons::events::shoot::shoot(
	entities::with_weapon &_from,
	pos_type const &_to
)
:
	from_(_from),
	to_(_to)
{}
	
sanguis::server::entities::with_weapon &
sanguis::server::weapons::events::shoot::from() const
{
	return from_;
}

sanguis::server::pos_type const &
sanguis::server::weapons::events::shoot::to() const
{
	return to_;
}