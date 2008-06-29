#include "enemy.hpp"
#include "../message_converter.hpp"
#include "../spawn_pickup.hpp"
#include "../../messages/add_enemy.hpp"

#include <cstdlib>

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

sanguis::messages::base *
sanguis::server::entities::enemy::add_message() const
{
	return message_convert<messages::add_enemy>(*this);
}

sanguis::entity_type::type
sanguis::server::entities::enemy::type() const
{
	return entity_type::enemy;
}

void sanguis::server::entities::enemy::on_die()
{
	get_environment().exp(exp());

	// TODO: use a random function from tr1?
	if(std::rand() % 10)
		spawn_pickup(center(), get_environment());
}
