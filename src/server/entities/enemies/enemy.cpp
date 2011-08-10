#include "enemy.hpp"
#include "../circle_from_dim.hpp"
#include "../default_solid.hpp"
#include "../exp_area.hpp"
#include "../insert_parameters_center.hpp"
#include "../property/initial.hpp"
#include "../spawns/spawn.hpp"
#include "../../ai/base.hpp"
#include "../../environment/load_context.hpp"
#include "../../environment/object.hpp"
#include "../../weapons/weapon.hpp"
#include "../../../random.hpp"
#include "../../../load/enemy_name.hpp"
#include "../../../messages/add_enemy.hpp"
#include "../../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::entities::enemies::enemy::enemy(
	sanguis::diff_clock const &_diff_clock,
	enemy_type::type const _etype,
	server::environment::load_context &_load_context,
	damage::armor const &_armor,
	server::health const _health,
	entities::movement_speed const _movement_speed,
	ai::create_function const &_ai,
	weapons::unique_ptr _weapon,
	server::probability const _spawn_chance,
	server::exp const _exp,
	auto_weak_link const _spawn_owner
)
:
	with_ai(
		_diff_clock,
		_ai,
		move(
			_weapon
		)
	),
	with_body(
		entities::circle_from_dim(
			_load_context.entity_dim(
				load::enemy_name(
					_etype
				)
			),
			entities::default_solid()
		)
	),
	with_buffs(),
	with_health(
		_diff_clock,
		_health,
		_armor
	),
	with_velocity(
		property::initial(
			_movement_speed.get(),
			0
		),
		server::direction(
			0
		)
	),
	etype_(_etype),
	spawn_chance_(_spawn_chance),
	exp_(_exp),
	spawn_owner_(_spawn_owner)
{
}

sanguis::server::entities::enemies::enemy::~enemy()
{
}

sanguis::enemy_type::type
sanguis::server::entities::enemies::enemy::etype() const
{
	return etype_;
}

void
sanguis::server::entities::enemies::enemy::on_update()
{
	with_ai::on_update();

	with_buffs::on_update();

	with_health::on_update();
}

sanguis::messages::auto_ptr
sanguis::server::entities::enemies::enemy::add_message(
	player_id const
) const
{
	return
		messages::create(
			messages::add_enemy(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->abs_speed().get(),
				this->current_health().get(),
				this->max_health().get(),
				this->etype()
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
sanguis::server::entities::enemies::enemy::on_remove()
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

	this->environment().insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::exp_area
			>(
				exp_
			)
		),
		entities::insert_parameters_center(
			this->center()
		)
	);

	this->environment().pickup_chance(
		spawn_chance_,
		this->center()
	);
}
