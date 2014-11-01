#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/load/model/enemy_path.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/aura_type_container.hpp>
#include <sanguis/messages/roles/buff_type_container.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <sanguis/messages/roles/enemy_kind.hpp>
#include <sanguis/messages/roles/enemy_type.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <sanguis/messages/server/add_enemy.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/entities/exp_area.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/movement_speed_initial.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/property/initial_zero.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
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
		_parameters.health(),
		_parameters.regeneration(),
		_parameters.armor()
	),
	sanguis::server::entities::with_links(),
	sanguis::server::entities::with_velocity(
		_parameters.load_context().model_size(
			sanguis::load::model::enemy_path(
				_parameters.enemy_type()
			)
		),
		sanguis::server::entities::movement_speed_initial(
			sanguis::server::entities::property::initial_zero(
				_parameters.movement_speed().get()
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
	)
{
}

sanguis::server::entities::enemies::enemy::~enemy()
{
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

sanguis::creator::enemy_type
sanguis::server::entities::enemies::enemy::enemy_type() const
{
	return
		enemy_type_;
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

sanguis::messages::server::unique_ptr
sanguis::server::entities::enemies::enemy::add_message(
	sanguis::server::player_id const,
	sanguis::collision::world::created const _created
) const
{
	return
		sanguis::messages::server::create_ptr(
			sanguis::messages::server::add_enemy(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					this->angle().get(),
				sanguis::messages::roles::created{} =
					_created.get(),
				sanguis::messages::roles::speed{} =
					this->speed().get(),
				sanguis::messages::roles::health{} =
					this->current_health().get(),
				sanguis::messages::roles::max_health{} =
					this->max_health().get(),
				sanguis::messages::roles::primary_weapon{} =
					this->primary_weapon_type(),
				sanguis::messages::roles::weapon_status{} =
					this->weapon_status(),
				sanguis::messages::roles::aura_type_container{} =
					this->aura_types(),
				sanguis::messages::roles::buff_type_container{} =
					this->buff_types(),
				sanguis::messages::roles::enemy_type{} =
					this->enemy_type(),
				sanguis::messages::roles::enemy_kind{} =
					this->enemy_kind(),
				sanguis::messages::roles::name{} =
					this->name()
			)
		);
}

sanguis::collision::world::body_group
sanguis::server::entities::enemies::enemy::collision_group() const
{
	return
		sanguis::collision::world::body_group::enemy;
}
