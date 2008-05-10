#include "enemy.hpp"

sanguis::server::entities::enemy::enemy(
	environment const &env,
	armor_array const &armor,
	messages::pos_type const &pos,
	messages::space_unit const angle,
	messages::space_unit const direction,
	team::type const team,
	const property_map &properties,
	ai::ai_ptr const ai_)
: entity_with_weapon(
	env,
	armor,
	pos,
	angle,
	direction,
	team,
	properties),
  ai_(ai_)
{}

void sanguis::server::entities::enemy::update(
	const time_type time,
	container &entities)
{
	entity_with_weapon::update(
		time,
		entities);
	ai_->update(
		time,
		entities);
}
