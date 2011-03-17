#include "environment.hpp"
#include "object.hpp"
#include "../entities/base.hpp"

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
	entity_id const _id,
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
	player_id const _player_id,
	entity_id const _id,
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
	entity_id const _id,
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
	entity_id const _id,
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
	entity_id const _id,
	health_type const _health
)
{
	world_.max_health_changed(
		_id,
		_health
	);
}

void
sanguis::server::world::environment::exp_changed(
	player_id const _player_id,
	entity_id const _entity_id,
	exp_type const _exp
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
	player_id const _player_id,
	entity_id const _entity_id,
	level_type const _level
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
	probability_type const _spawn_chance,
	pos_type const &_center
)
{
	world_.pickup_chance(
		_spawn_chance,
		_center
	);
}

void
sanguis::server::world::environment::request_transfer(
	world_id const _world_id,
	entity_id const _entity_id,
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
	player_id const _player_id,
	entity_id const _target_id
)
{
	world_.add_sight_range(
		_player_id,
		_target_id
	);
}

void
sanguis::server::world::environment::remove_sight_range(
	player_id const _player_id,
	entity_id const _target_id
)
{
	world_.remove_sight_range(
		_player_id,
		_target_id
	);
}

void
sanguis::server::world::environment::remove_player(
	player_id const _player_id
)
{
	world_.remove_player(
		_player_id
	);
}

sge::collision::world_ptr const
sanguis::server::world::environment::collision_world() const
{
	return world_.collision_world();
}

sanguis::server::collision::global_groups const &
sanguis::server::world::environment::global_collision_groups() const
{
	return world_.global_collision_groups();
}

sanguis::server::environment::load_context_ptr const
sanguis::server::world::environment::load_context() const
{
	return world_.load_context();
}
