#include "enemy.hpp"

sanguis::server::entities::enemy::enemy(
	send_callback const &send_callback_,
	insert_callback const &insert_callback_,
	messages::pos_type const &pos,
	const messages::space_unit angle,
	const messages::space_unit direction,
	const messages::space_unit health,
	const messages::space_unit max_health,
	const team::type team,
	const messages::space_unit speed,
	weapons::weapon_ptr weapon_,
	const ai::ai_ptr ai_)
: entity_with_weapon(
	send_callback_,
	insert_callback_,
	pos,
	angle,
	direction,
	health,
	max_health,
	team,
	speed,
	weapon_),
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
