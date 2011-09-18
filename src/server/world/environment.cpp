#include <sanguis/server/world/environment.hpp>
#include <sanguis/server/world/object.hpp>
#include <sanguis/server/entities/base.hpp>

sanguis::server::world::environment::environment(
	world::object &_world
)
:
	world_(_world)
{
}

sanguis::server::world::environment::~environment()
{
}

void
sanguis::server::world::environment::insert(
	entities::unique_ptr _entity,
	entities::insert_parameters const &_param
)
{
	world_.insert(
		move(
			_entity
		),
		_param
	);
}

void
sanguis::server::world::environment::weapon_changed(
	sanguis::entity_id const _id,
	weapon_type::type const _weapon
)
{
	world_.weapon_changed(
		_id,
		_weapon
	);
}

void
sanguis::server::world::environment::got_weapon(
	server::player_id const _player_id,
	sanguis::entity_id const _id,
	weapon_type::type const _weapon
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
	server::health const _health
)
{
	world_.max_health_changed(
		_id,
		_health
	);
}

void
sanguis::server::world::environment::exp_changed(
	server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	server::exp const _exp
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
	server::player_id const _player_id,
	sanguis::entity_id const _entity_id,
	server::level const _level
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
	server::probability const _spawn_chance,
	server::center const &_center
)
{
	world_.pickup_chance(
		_spawn_chance,
		_center
	);
}

void
sanguis::server::world::environment::request_transfer(
	sanguis::world_id const _world_id,
	sanguis::entity_id const _entity_id,
	entities::insert_parameters const &_insert_parameters
)
{
	world_.request_transfer(
		_world_id,
		_entity_id,
		_insert_parameters
	);
}

void
sanguis::server::world::environment::add_sight_range(
	server::player_id const _player_id,
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
	server::player_id const _player_id,
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
	server::player_id const _player_id
)
{
	world_.remove_player(
		_player_id
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
