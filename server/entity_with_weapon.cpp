#include "entity_with_weapon.hpp"
#include <limits>

namespace
{

const sanguis::messages::pos_type target_undefined(
	std::numeric_limits<sanguis::messages::space_unit>::max(),
	std::numeric_limits<sanguis::messages::space_unit>::max());

}

sanguis::server::entity_with_weapon::entity_with_weapon(
	send_callback const &send_callback_,
	messages::pos_type const &pos_,
	const messages::space_unit angle_,
	const messages::space_unit direction_,
	const messages::space_unit health_,
	const messages::space_unit max_health_,
	const team::type team_,
	const messages::space_unit speed_,
	weapons::weapon_ptr weapon_)
: entity(
	send_callback_,
	pos_,
	angle_,
	direction_,
	health_,
	max_health_,
	team_,
	speed_),
  weapon_(weapon_),
  target_(target_undefined)
{}

void sanguis::server::entity_with_weapon::update(
	const time_type time,
	entity_container &entities)
{
	entity::update(
		time,
		entities);

	if(weapon_ && target() != target_undefined && attacking())
		weapon_->attack(*this, target());
	// TODO: start_attacking goes here
}

void sanguis::server::entity_with_weapon::change_weapon(
	const weapons::weapon_ptr nweapon)
{
	weapon_ = nweapon;
}

void sanguis::server::entity_with_weapon::target(
	messages::pos_type const &ntarget)
{
	target_ = ntarget;
}

sanguis::messages::pos_type const &
sanguis::server::entity_with_weapon::target() const
{
	return target_;
}
