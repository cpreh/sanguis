#include "enemy.hpp"
#include "../base_parameters.hpp"
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
	messages::pos_type const &center,
	messages::space_unit const angle,
	messages::space_unit const direction,
	property_map const &properties,
	ai::ai_ptr const ai_,
	weapons::weapon_ptr weapon_,
	unsigned const spawn_chance,
	messages::exp_type const exp_)
:
	entity_with_ai(
		base_parameters(
			env,
			armor,
			center,
			angle,
			direction,
			team::monsters,
			properties,
			entity_type::enemy,
			false,
			default_dim(
				load::enemy_name(
					etype_))),
		ai_,
		weapon_),
	  etype_(etype_),
	  spawn_chance(spawn_chance),
	  exp_(exp_)
{}

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

sanguis::messages::exp_type
sanguis::server::entities::enemies::enemy::exp() const
{
	return exp_;
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
