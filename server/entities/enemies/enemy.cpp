#include "enemy.hpp"
#include "../base_parameters.hpp"
#include "../../weapons/weapon.hpp"
#include "../../ai/base.hpp"
#include "../../environment/load_context.hpp"
#include "../../../random.hpp"
#include "../../../load/enemy_name.hpp"
#include "../../../messages/add_enemy.hpp"
#include "../../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sanguis::server::entities::enemies::enemy::enemy(
	enemy_type::type const etype_,
	server::environment::load_context_ptr const load_context_,
	damage::armor const &armor,
	property_map const &properties,
	ai::auto_ptr ai_,
	weapons::auto_ptr weapon_,
	probability_type const spawn_chance,
	exp_type const exp_
)
:
	with_ai(
		base_parameters(
			team::monsters,
			properties,
			entity_type::enemy,
			false,
			load_context_->entity_dim(
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

void
sanguis::server::entities::enemies::enemy::on_die()
{
	/*
	environment().exp()(
		exp_
	);
	// TODO

	if(
		environment().pickup_chance()(
			spawn_chance
		)
	)
		environment().spawn_pickup()(
			center()
		);
	*/
}
