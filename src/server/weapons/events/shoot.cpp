#include <sanguis/server/vector.hpp>
#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>


sanguis::server::weapons::events::shoot::shoot(
	sanguis::server::entities::with_weapon &_from,
	sanguis::server::vector const &_to
)
:
	from_(
		_from
	),
	to_(
		_to
	)
{
}

sanguis::server::entities::with_weapon &
sanguis::server::weapons::events::shoot::from() const
{
	return from_;
}

sanguis::server::vector const &
sanguis::server::weapons::events::shoot::to() const
{
	return to_;
}
