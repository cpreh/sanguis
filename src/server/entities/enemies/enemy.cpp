#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/entity_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <sanguis/messages/add_enemy.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/circle_from_dim.hpp>
#include <sanguis/server/entities/default_solid.hpp>
#include <sanguis/server/entities/exp_area.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/spawn_owner.hpp>
#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::enemy::enemy(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::enemy_type const _etype,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::damage::armor const &_armor,
	sanguis::server::health const _health,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::ai::create_function const &_ai,
	sanguis::server::weapons::unique_ptr _weapon,
	sanguis::server::pickup_probability const _spawn_chance,
	sanguis::server::exp const _exp,
	sanguis::server::entities::enemies::spawn_owner const &_spawn_owner
)
:
	sanguis::server::entities::with_ai(
		_diff_clock,
		_random_generator,
		_ai,
		std::move(
			_weapon
		)
	),
	sanguis::server::entities::with_body(
		sanguis::server::entities::circle_from_dim(
			_load_context.entity_dim(
				sanguis::load::enemy_name(
					_etype
				)
			),
			sanguis::server::entities::default_solid()
		)
	),
	sanguis::server::entities::with_buffs(),
	sanguis::server::entities::with_health(
		_diff_clock,
		_health,
		_armor
	),
	sanguis::server::entities::with_velocity(
		sanguis::server::entities::property::initial(
			sanguis::server::entities::property::initial::base(
				_movement_speed.get()
			),
			sanguis::server::entities::property::initial::current(
				0.f
			)
		),
		sanguis::server::direction(
			0.f
		)
	),
	etype_(
		_etype
	),
	spawn_chance_(
		_spawn_chance
	),
	exp_(
		_exp
	),
	spawn_owner_(
		_spawn_owner
	)
{
}

sanguis::server::entities::enemies::enemy::~enemy()
{
}

sanguis::enemy_type
sanguis::server::entities::enemies::enemy::etype() const
{
	return etype_;
}

void
sanguis::server::entities::enemies::enemy::on_update()
{
	sanguis::server::entities::with_ai::on_update();

	sanguis::server::entities::with_buffs::on_update();

	sanguis::server::entities::with_health::on_update();
}

sanguis::messages::auto_ptr
sanguis::server::entities::enemies::enemy::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::create(
			sanguis::messages::add_enemy(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->speed().get(),
				this->current_health().get(),
				this->max_health().get(),
				static_cast<
					sanguis::messages::types::enum_
				>(
					this->etype()
				)
			)
		);
}

sanguis::entity_type
sanguis::server::entities::enemies::enemy::type() const
{
	return sanguis::entity_type::enemy;
}

sanguis::server::team
sanguis::server::entities::enemies::enemy::team() const
{
	return sanguis::server::team::monsters;
}

void
sanguis::server::entities::enemies::enemy::on_remove()
{
	if(
		spawn_owner_.get()
	)
		dynamic_cast<
			sanguis::server::entities::spawns::spawn &
		>(
			*spawn_owner_.get()
		)
		.unregister(
			*this
		);

	this->environment().insert(
		fcppt::make_unique_ptr<
			sanguis::server::entities::exp_area
		>(
			exp_
		),
		sanguis::server::entities::insert_parameters_center(
			this->center()
		)
	);

	this->environment().pickup_chance(
		spawn_chance_,
		this->center()
	);
}
