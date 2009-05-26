#include "health.hpp"
#include "../entity_with_weapon.hpp"
#include <sge/optional_impl.hpp>

sanguis::server::entities::pickups::health::health(
	server::environment const &env,
	pos_type const &center,
	team::type const team_,
	health_type const amount)
:
	pickup(
		pickup_type::health,
		env,
		center,
		team_,
		optional_dim()
	),
	amount(amount)
{}

void sanguis::server::entities::pickups::health::do_pickup(
	entity_with_weapon &receiver)
{
	receiver.health(receiver.health() + amount);	
}
