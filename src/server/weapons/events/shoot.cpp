#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>


sanguis::server::weapons::events::shoot::shoot(
	sanguis::server::entities::with_weapon &_from
)
:
	from_(
		_from
	)
{
}

sanguis::server::entities::with_weapon &
sanguis::server::weapons::events::shoot::from() const
{
	return from_;
}
