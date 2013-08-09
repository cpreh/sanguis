#include <sanguis/entity_id.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/world/environment.hpp>
#include <sanguis/server/world/object.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::environment::environment(
	sanguis::server::world::object &_world
)
:
	sanguis::server::environment::object(),
	world_(
		_world
	)
{
}

sanguis::server::world::environment::~environment()
{
}

sanguis::server::entities::optional_base_ref const
sanguis::server::world::environment::insert(
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_param
)
{
	return
		world_.insert(
			std::move(
				_entity
			),
			_param
		);
}

void
sanguis::server::world::environment::weapon_changed(
	sanguis::entity_id const _id,
	sanguis::primary_weapon_type const _weapon
)
{
	world_.weapon_changed(
		_id,
		_weapon
	);
}

void
sanguis::server::world::environment::got_weapon(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _id,
	sanguis::weapon_type const _weapon
)
{
	world_.got_weapon(
		_player_id,
		_id,
		_weapon
	);
}

void
sanguis::server::world::environment::attacking_changed(
	sanguis::entity_id const _id,
	bool const _is_attacking
)
{
	world_.attacking_changed(
		_id,
		_is_attacking
	);
}

void
sanguis::server::world::environment::reloading_changed(
	sanguis::entity_id const _id,
	bool const _is_reloading
)
{
	world_.reloading_changed(
		_id,
		_is_reloading
	);
}

void
sanguis::server::world::environment::max_health_changed(
	sanguis::entity_id const _id,
	sanguis::server::health const _health
)
{
	world_.max_health_changed(
		_id,
		_health
	);
}

void
sanguis::server::world::environment::exp_changed(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	sanguis::server::exp const _exp
)
{
	world_.exp_changed(
		_player_id,
		_entity_id,
		_exp
	);
}

void
sanguis::server::world::environment::level_changed(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	sanguis::server::level const _level
)
{
	world_.level_changed(
		_player_id,
		_entity_id,
		_level
	);
}

void
sanguis::server::world::environment::pickup_chance(
	sanguis::server::pickup_probability const _spawn_chance,
	sanguis::server::center const &_center
)
{
	world_.pickup_chance(
		_spawn_chance,
		_center
	);
}

void
sanguis::server::world::environment::add_sight_range(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _target_id
)
{
	world_.add_sight_range(
		_player_id,
		_target_id
	);
}

void
sanguis::server::world::environment::remove_sight_range(
	sanguis::server::player_id const _player_id,
	sanguis::entity_id const _target_id
)
{
	world_.remove_sight_range(
		_player_id,
		_target_id
	);
}

void
sanguis::server::world::environment::remove_player(
	sanguis::server::player_id const _player_id
)
{
	world_.remove_player(
		_player_id
	);
}

void
sanguis::server::world::environment::request_transfer(
	sanguis::entity_id const _id
)
{
	world_.request_transfer(
		_id
	);
}

sge::projectile::world &
sanguis::server::world::environment::collision_world() const
{
	return world_.collision_world();
}

sanguis::server::collision::global_groups const &
sanguis::server::world::environment::global_collision_groups() const
{
	return world_.global_collision_groups();
}

sanguis::server::environment::load_context &
sanguis::server::world::environment::load_context() const
{
	return world_.load_context();
}
