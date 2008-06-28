#include "enemy.hpp"

sanguis::enemy_type::type
sanguis::server::entities::enemy::etype() const
{
	return etype_;
}

sanguis::server::entities::enemy::enemy(
	enemy_type::type const etype_,
	environment const &env,
	armor_array const &armor,
	messages::pos_type const &pos,
	messages::space_unit const angle,
	messages::space_unit const direction,
	team::type const team,
	property_map const &properties,
	ai::ai_ptr const ai_)
: entity_with_weapon(
	env,
	armor,
	pos,
	angle,
	direction,
	team,
	properties),
  ai_(ai_),
  etype_(etype_)
{}

void sanguis::server::entities::enemy::update(
	time_type const time,
	container &entities)
{
	entity_with_weapon::update(
		time,
		entities);
	ai_->update(
		time,
		entities);
}

sanguis::entity_type::type
sanguis::server::entities::enemy::type() const
{
	return entity_type::enemy;
}
