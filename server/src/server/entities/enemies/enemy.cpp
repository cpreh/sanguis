#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <sanguis/messages/server/add_enemy.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/exp_area.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::enemy::enemy(
	sanguis::server::entities::enemies::parameters &&_parameters
)
:
	sanguis::server::entities::with_ai(
		_parameters.diff_clock(),
		_parameters.random_generator(),
		_parameters.ai_create_function(),
		std::move(
			_parameters.weapon()
		),
		std::move(
			_parameters.auras()
		),
		_parameters.ias(),
		_parameters.irs()
	),
	sanguis::server::entities::with_buffs(),
	sanguis::server::entities::with_id(
		_parameters.load_context().next_id()
	),
	sanguis::server::entities::with_health(
		_parameters.diff_clock(),
		_parameters.health(),
		_parameters.regeneration(),
		_parameters.armor()
	),
	sanguis::server::entities::with_links(),
	sanguis::server::entities::with_velocity(
		_parameters.diff_clock(),
		_parameters.load_context().entity_dim(
			sanguis::server::model_name(
				sanguis::load::enemy_name(
					_parameters.enemy_type()
				)
			)
		),
		sanguis::server::entities::property::initial(
			sanguis::server::entities::property::initial::base(
				_parameters.movement_speed().get()
			),
			sanguis::server::entities::property::initial::current(
				0.f
			)
		),
		sanguis::server::direction(
			0.f
		)
	),
	enemy_type_(
		_parameters.enemy_type()
	),
	pickup_probability_(
		_parameters.pickup_probability()
	),
	exp_(
		_parameters.exp()
	),
	difficulty_(
		_parameters.difficulty()
	),
	spawn_owner_(
		_parameters.spawn_owner()
	),
	name_(
		sge::charconv::fcppt_string_to_utf8(
			sanguis::load::enemy_name(
				enemy_type_
			)
		)
	)
{
}

sanguis::server::entities::enemies::enemy::~enemy()
{
}

sanguis::creator::enemy_type
sanguis::server::entities::enemies::enemy::enemy_type() const
{
	return
		enemy_type_;
}

sanguis::server::team
sanguis::server::entities::enemies::enemy::team() const
{
	return
		sanguis::server::team::monsters;
}

void
sanguis::server::entities::enemies::enemy::update()
{
	sanguis::server::entities::with_ai::update();

	sanguis::server::entities::with_buffs::update();

	sanguis::server::entities::with_health::update();

	sanguis::server::entities::with_velocity::update();
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::enemies::enemy::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::server::create_ptr(
			sanguis::messages::server::add_enemy(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->speed().get(),
				this->current_health().get(),
				this->max_health().get(),
				this->primary_weapon_type(),
				this->weapon_status(),
				this->aura_types(),
				this->buff_types(),
				this->enemy_type(),
				this->name()
			)
		);
}

sanguis::collision::world::group_field const
sanguis::server::entities::enemies::enemy::collision_groups() const
{
	return
		sanguis::collision::world::group_field{
			sanguis::collision::world::group::enemy
		};
}

void
sanguis::server::entities::enemies::enemy::remove()
{
	if(
		spawn_owner_.get()
	)
		fcppt::cast::static_downcast<
			sanguis::server::entities::spawns::spawn &
		>(
			*spawn_owner_.get()
		)
		.unregister(
			*this
		);

	sanguis::server::environment::insert_no_result(
		*this->environment(),
		fcppt::make_unique_ptr<
			sanguis::server::entities::exp_area
		>(
			exp_
		),
		sanguis::server::entities::insert_parameters_center(
			this->center()
		)
	);

	this->environment()->pickup_chance(
		pickup_probability_,
		difficulty_,
		this->center()
	);
}

sanguis::messages::types::string const &
sanguis::server::entities::enemies::enemy::name() const
{
	return
		name_;
}