#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/events/reload.hpp>


sanguis::server::weapons::events::reload::reload(
	sanguis::server::entities::with_weapon &_from
)
:
	from_(
		_from
	)
{
}

sanguis::server::entities::with_weapon &
sanguis::server::weapons::events::reload::from() const
{
	return from_;
}
