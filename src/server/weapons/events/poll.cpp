#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/events/poll.hpp>


sanguis::server::weapons::events::poll::poll(
	sanguis::server::entities::with_weapon &_owner
)
:
	owner_(
		_owner
	)
{
}

sanguis::server::entities::with_weapon &
sanguis::server::weapons::events::poll::owner() const
{
	return owner_;
}
