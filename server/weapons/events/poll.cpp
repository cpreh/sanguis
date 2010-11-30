#include "poll.hpp"

sanguis::server::weapons::events::poll::poll(
	time_type const _time,
	entities::with_weapon &_owner
)
:
	time_(_time),
	owner_(_owner)
{}
	
sanguis::time_type
sanguis::server::weapons::events::poll::time() const
{
	return time_;
}

sanguis::server::entities::with_weapon &
sanguis::server::weapons::events::poll::owner() const
{
	return owner_;
}
