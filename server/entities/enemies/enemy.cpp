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
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::entities::enemies::enemy::enemy(
	enemy_type::type const _etype,
	server::environment::load_context_ptr const _load_context,
	damage::armor const &_armor,
	entities::health_type const _health,
	entities::movement_speed const _movement_speed,
	ai::create_function const &_ai,
	weapons::unique_ptr _weapon,
	probability_type const _spawn_chance,
	exp_type const _exp,
	auto_weak_link const _spawn_owner
)
:
	with_ai(
		_ai,
		move(
			_weapon
		)
	),
	with_buffs(),
	with_dim(
		_load_context->entity_dim(
			load::enemy_name(
				_etype
			)
		)
	),	
	with_health(
		_health,
		_armor
	),
	movable(
		property::initial(
			_movement_speed,
			0
		),
		static_cast<space_unit>(0)
	),
	etype_(_etype),
	spawn_chance_(_spawn_chance),
	exp_(_exp),
	spawn_owner_(_spawn_owner)
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
		unique_ptr(
			fcppt::make_unique_ptr<
				entities::exp_area
			>(
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
