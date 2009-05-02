#include "poll.hpp"

sanguis::server::weapons::events::poll::poll(
	time_type const time_,
	entities::entity_with_weapon &owner_)
:
	time_(time_),
	owner_(owner_)
{}
	
sanguis::time_type
sanguis::server::weapons::events::poll::time() const
{
	return time_;
}

sanguis::server::entities::entity_with_weapon &
sanguis::server::weapons::events::poll::owner() const
{
	return owner_;
}
