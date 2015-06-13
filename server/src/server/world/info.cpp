#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/server/world/info.hpp>


sanguis::server::world::info::info(
	sanguis::world_id const _world_id,
	sanguis::world_name const &_world_name,
	sanguis::creator::seed const _seed,
	sanguis::creator::name const &_generator_name,
	sanguis::creator::spawn_boss const _spawn_boss,
	sanguis::creator::opening_container_array const &_openings
)
:
	world_id_(
		_world_id
	),
	world_name_(
		_world_name
	),
	seed_(
		_seed
	),
	generator_name_(
		_generator_name
	),
	spawn_boss_(
		_spawn_boss
	),
	openings_(
		_openings
	)
{
}

sanguis::world_id const
sanguis::server::world::info::world_id() const
{
	return
		world_id_;
}

sanguis::world_name const &
sanguis::server::world::info::world_name() const
{
	return
		world_name_;
}

sanguis::creator::seed const
sanguis::server::world::info::seed() const
{
	return
		seed_;
}

sanguis::creator::name const &
sanguis::server::world::info::generator_name() const
{
	return
		generator_name_;
}

sanguis::creator::spawn_boss const
sanguis::server::world::info::spawn_boss() const
{
	return
		spawn_boss_;
}

sanguis::creator::opening_container_array const &
sanguis::server::world::info::openings() const
{
	return
		openings_;
}
