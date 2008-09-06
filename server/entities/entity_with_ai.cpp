#include "entity_with_ai.hpp"

sanguis::server::entities::entity_with_ai::entity_with_ai(
	environment const &env,
	armor_array const &armor,
	messages::pos_type const &pos,
	messages::space_unit const angle,
	messages::space_unit const direction,
	team::type const team_,
	entity::property_map const &properties,
	ai::ai_ptr ai_,
	weapons::weapon_ptr start_weapon)
:
	entity_with_weapon(
		env,
		armor,
		pos,
		angle,
		direction,
		team_,
		properties,
		start_weapon),
	ai_(ai_)
{}

void sanguis::server::entities::entity_with_ai::update(
	time_type const time,
	container &entities)
{
	entity_with_weapon::update(
		time,
		entities);
	
	ai_->update(
		*this,
		time,
		entities);
}
