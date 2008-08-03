#include "health.hpp"
#include "../entity_with_weapon.hpp"
#include "../../get_dim.hpp"

sanguis::server::entities::pickups::health::health(
	environment const &env,
	messages::pos_type const &pos,
	team::type const team_,
	messages::space_unit const amount)
: pickup(
	pickup_type::health,
	env,
	pos,
	team_),
  amount(amount)
{}

void sanguis::server::entities::pickups::health::do_pickup(
	entity_with_weapon &receiver)
{
	receiver.health(receiver.health() + amount);	
}

sanguis::messages::dim_type const
sanguis::server::entities::pickups::health::dim() const
{
	return get_dim(
		SGE_TEXT("pickup_hp"),
		SGE_TEXT("default")
		);
}
