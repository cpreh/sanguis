#include "entity_with_weapon.hpp"
#include "../message_converter.hpp"
#include <limits>

namespace
{

const sanguis::messages::pos_type target_undefined(
	std::numeric_limits<sanguis::messages::space_unit>::max(),
	std::numeric_limits<sanguis::messages::space_unit>::max());

}

sanguis::server::entities::entity_with_weapon::entity_with_weapon(
	environment const &env,
	armor_array const &armor,
	messages::pos_type const &pos_,
	const messages::space_unit angle_,
	const messages::space_unit direction_,
	const team::type team_,
	const entity::property_map &properties)
: entity(
	env,
	armor,
	pos_,
	angle_,
	direction_,
	team_,
	properties
	),
	weapon_(weapon_type::none),
  target_(target_undefined)
{
}

void sanguis::server::entities::entity_with_weapon::update(
	const time_type time,
	container &entities)
{
	entity::update(
		time,
		entities);
	
	// entity lost its target and/or weapon or aggression or didn't have any of these
	if (weapon_ == weapon_type::none || target() == target_undefined || !aggressive())
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
	if (weapon_ != weapon_type::none && target() != target_undefined && aggressive())
	{
		if (weapons_.find(weapon_)->second->attack(*this,target()))
		{
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

void sanguis::server::entities::entity_with_weapon::change_weapon(const weapon_type::type nweapon)
{
	if (nweapon != weapon_type::none && weapons_.find(nweapon) == weapons_.end())
		throw sge::exception(SGE_TEXT("tried to change to non-owned weapon"));

	weapon_ = nweapon;
}

void sanguis::server::entities::entity_with_weapon::add_weapon(weapons::weapon_ptr ptr)
{
	if (weapons_.find(ptr->type()) != weapons_.end())
		throw sge::exception(SGE_TEXT("weapon of specified type already registered"));

	const weapon_type::type wt = ptr->type();
	if (!weapons_.insert(wt,ptr).second)
		throw sge::exception(SGE_TEXT("couldn't insert weapon"));
}

void sanguis::server::entities::entity_with_weapon::remove_weapon(const weapon_type::type type_)
{
	if (weapons_.find(type_) == weapons_.end())
		throw sge::exception(SGE_TEXT("tried to remove non-owned weapon"));
	
	weapons_.erase(type_);
}

void sanguis::server::entities::entity_with_weapon::target(
	messages::pos_type const &ntarget)
{
	target_ = ntarget;
}

sanguis::messages::pos_type const &
sanguis::server::entities::entity_with_weapon::target() const
{
	return target_;
}
