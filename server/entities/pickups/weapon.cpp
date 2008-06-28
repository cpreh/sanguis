#include "weapon.hpp"
#include "../entity_with_weapon.hpp"
#include "../../weapons/factory.hpp"

sanguis::server::entities::pickups::weapon::weapon(
	environment const &env,
	messages::pos_type const &pos,
	messages::space_unit const angle,
	messages::space_unit const direction,
	team::type const team_,
	weapon_type::type const weapon_type_)
: pickup(
	pickup_type::weapon,
	env,
	pos,
	angle,
	direction,
	team_),
  weapon_type_(weapon_type_)
{}

void sanguis::server::entities::pickups::weapon::do_pickup(
	entity_with_weapon &receiver)
{
	receiver.add_weapon(
		weapons::create(
			weapon_type_,
			get_environment()));
}
