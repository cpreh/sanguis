#include "enemy.hpp"

sanguis::server::entities::enemy::enemy(
	environment const &env,
	armor_array const &armor,
	messages::pos_type const &pos,
	messages::space_unit const angle,
	messages::space_unit const direction,
	messages::space_unit const health,
	messages::space_unit const max_health,
	team::type const team,
	messages::space_unit const speed,
	ai::ai_ptr const ai_)
: entity_with_weapon(
	env,
	armor,
	pos,
	angle,
	direction,
	health,
	max_health,
	team,
	speed),
  ai_(ai_)
{}

void sanguis::server::entities::enemy::update(
	const time_type time,
	entity_container &entities)
{
	entity_with_weapon::update(
		time,
		entities);
	ai_->update(
		time,
		entities);
}
