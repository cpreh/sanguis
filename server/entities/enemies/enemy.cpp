#include "enemy.hpp"
#include "../base_parameters.hpp"
#include "../../weapons/weapon.hpp"
#include "../../ai/base.hpp"
#include "../../get_dim.hpp"
#include "../../environment.hpp"
#include "../../../random.hpp"
#include "../../../load/enemy_name.hpp"
#include "../../../load/context.hpp"
#include "../../../messages/add_enemy.hpp"
#include "../../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sanguis::server::entities::enemies::enemy::enemy(
	enemy_type::type const etype_,
	server::environment const &env,
	armor_array const &armor,
	pos_type const &center,
	space_unit const angle,
	space_unit const direction,
	property_map const &properties,
	ai::auto_ptr ai_,
	weapons::auto_ptr weapon_,
	probability_type const spawn_chance,
	exp_type const exp_)
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
				env.load().models(),
				load::enemy_name(
					etype_
				)
			)
		),
		ai_,
		weapon_
	),
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
	return messages::create(
		messages::add_enemy(
			id(),
			pos(),
			angle(),
			abs_speed(),
			health(),
			max_health(),
			dim(),
			etype()
		)
	);
}

sanguis::server::exp_type
sanguis::server::entities::enemies::enemy::exp() const
{
	return exp_;
}

void sanguis::server::entities::enemies::enemy::on_die()
{
	environment().exp(exp());

	if(
		environment().pickup_chance(
			spawn_chance
		)
	)
		environment().spawn_pickup(
			center()
		);
}
