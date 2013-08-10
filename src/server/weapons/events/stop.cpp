#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/events/stop.hpp>


sanguis::server::weapons::events::stop::stop(
	sanguis::server::entities::with_weapon &_owner
)
:
	owner_(
		_owner
	)
{
}

sanguis::server::entities::with_weapon &
sanguis::server::weapons::events::stop::owner() const
{
	return owner_;
}
