#include "enemy.hpp"
#include "../../message_converter.hpp"
#include "../../spawn_pickup.hpp"
#include "../../get_dim.hpp"
#include "../../../random.hpp"
#include "../../../load/enemy_name.hpp"
#include "../../../messages/add_enemy.hpp"
#include <boost/tr1/random.hpp>

sanguis::server::entities::enemies::enemy::enemy(
	enemy_type::type const etype_,
	environment const &env,
	armor_array const &armor,
	messages::pos_type const &pos,
	messages::space_unit const angle,
	messages::space_unit const direction,
	property_map const &properties,
	ai::ai_ptr const ai_,
	weapons::weapon_ptr weapon_,
	unsigned const spawn_chance,
	messages::exp_type const exp_)
: entity_with_weapon(
	env,
	armor,
	pos,
	angle,
	direction,
	team::monsters,
	properties),
  ai_(ai_),
  etype_(etype_),
  spawn_chance(spawn_chance),
  exp_(exp_)
{
	weapon_type::type const wtype(
		weapon_->type());
	add_weapon(
		weapon_);
	change_weapon(
		wtype);
}

void sanguis::server::entities::enemies::enemy::update(
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

sanguis::enemy_type::type
sanguis::server::entities::enemies::enemy::etype() const
{
	return etype_;
}

sanguis::messages::auto_ptr
sanguis::server::entities::enemies::enemy::add_message() const
{
	return message_convert<messages::add_enemy>(*this);
}

sanguis::entity_type::type
sanguis::server::entities::enemies::enemy::type() const
{
	return entity_type::enemy;
}

sanguis::messages::dim_type const
sanguis::server::entities::enemies::enemy::dim() const
{
	return get_dim(
		load::enemy_name(
			etype()),
		SGE_TEXT("default"));
}

sanguis::messages::exp_type
sanguis::server::entities::enemies::enemy::exp() const
{
	return exp_;
}

bool sanguis::server::entities::enemies::enemy::invulnerable() const
{
	return false;
}

void sanguis::server::entities::enemies::enemy::on_die()
{
	get_environment().exp(exp());

	typedef std::tr1::uniform_int<
		unsigned
	> uniform_ui;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		uniform_ui
	> rng_type;

	static rng_type rng(
		create_seeded_randgen(),
		uniform_ui(
			0,
			4
		));

	if(rng() <= spawn_chance)
		spawn_pickup(center(), get_environment());
}
