#include "enemy.hpp"
#include "../exp_area.hpp"
#include "../insert_parameters_pos.hpp"
#include "../property/initial.hpp"
#include "../spawns/spawn.hpp"
#include "../../weapons/weapon.hpp"
#include "../../ai/base.hpp"
#include "../../environment/load_context.hpp"
#include "../../environment/object.hpp"
#include "../../../random.hpp"
#include "../../../load/enemy_name.hpp"
#include "../../../messages/add_enemy.hpp"
#include "../../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::server::entities::enemies::enemy::enemy(
	enemy_type::type const etype_,
	server::environment::load_context_ptr const load_context_,
	damage::armor const &armor_,
	entities::health_type const health_,
	entities::movement_speed const movement_speed_,
	ai::create_function const &ai_,
	weapons::auto_ptr weapon_,
	probability_type const spawn_chance_,
	exp_type const exp_,
	auto_weak_link const spawn_owner
)
:
	with_ai(
		ai_,
		weapon_
	),
	with_buffs(),
	with_dim(
		load_context_->entity_dim(
			load::enemy_name(
				etype_
			)
		)
	),	
	with_health(
		health_,
		armor_
	),
	movable(
		property::initial(
			movement_speed_,
			0
		),
		static_cast<space_unit>(0)
	),
	etype_(etype_),
	spawn_chance_(spawn_chance_),
	exp_(exp_),
	spawn_owner_(spawn_owner_)
{}

sanguis::enemy_type::type
sanguis::server::entities::enemies::enemy::etype() const
{
	return etype_;
}

void
sanguis::server::entities::enemies::enemy::on_update(
	time_type const time_
)
{
	with_ai::on_update(
		time_
	);

	with_buffs::on_update(
		time_
	);

	with_health::on_update(
		time_
	);
}

sanguis::messages::auto_ptr
sanguis::server::entities::enemies::enemy::add_message(
	player_id const
) const
{
	return messages::create(
		messages::add_enemy(
			id(),
			pos(),
			angle(),
			dim(),
			abs_speed(),
			current_health(),
			max_health(),
			etype()
		)
	);
}

sanguis::entity_type::type
sanguis::server::entities::enemies::enemy::type() const
{
	return entity_type::enemy;
}

sanguis::server::team::type
sanguis::server::entities::enemies::enemy::team() const
{
	return server::team::monsters;
}

void
sanguis::server::entities::enemies::enemy::on_die()
{
	if(
		spawn_owner_
	)
		dynamic_cast<
			spawns::spawn &
		>(
			*spawn_owner_
		)
		.unregister(
			*this
		);

	environment()->insert(
		auto_ptr(
			new entities::exp_area(
				exp_
			)
		),
		insert_parameters_pos(
			center()
		)
	);

	environment()->pickup_chance(
		spawn_chance_,
		center()
	);
}
