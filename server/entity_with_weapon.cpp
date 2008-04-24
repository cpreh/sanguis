#include "entity_with_weapon.hpp"
#include "message_converter.hpp"
#include <sge/iostream.hpp>
#include <limits>

namespace
{

const sanguis::messages::pos_type target_undefined(
	std::numeric_limits<sanguis::messages::space_unit>::max(),
	std::numeric_limits<sanguis::messages::space_unit>::max());

}

sanguis::server::entity_with_weapon::entity_with_weapon(
	send_callback const &send_callback_,
	insert_callback const &insert_callback_,
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
	insert_callback_,
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
	
	// entity lost it's target and/or weapon or aggression or didn't have any of these
	if (!weapon_ || target() == target_undefined || !aggressive())
	{
		// previously attacking
		if (attacking())
		{
			send(message_convert<messages::stop_attacking>(*this));
			attacking(false);
		}

		return;
	}

	// all requirements for an attack are met?
	// -has a weapon
	// -has a target
	// -is aggressive
	if (weapon_ && target() != target_undefined && aggressive())
	{
		if (weapon_->attack(*this,target()))
		{
			sge::cout << SGE_TEXT("server: attacking returned true\n");
			if (!attacking())
			{
				send(message_convert<messages::start_attacking>(*this));
				attacking(true);
			}
		}
		else
		{
			if (attacking())
			{
				send(message_convert<messages::stop_attacking>(*this));
				attacking(false);
			}
		}
	}
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
