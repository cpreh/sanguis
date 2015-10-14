#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/top_result.hpp>


sanguis::creator::top_result::top_result(
	sanguis::creator::seed const _seed,
	sanguis::creator::name const &_name,
	sanguis::creator::spawn_boss const _spawn_boss,
	sanguis::creator::grid const &_grid,
	sanguis::creator::background_grid const &_background_grid,
	sanguis::creator::opening_container_array const &_openings,
	sanguis::creator::spawn_container const &_spawns,
	sanguis::creator::destructible_container const &_destructibles
)
:
	seed_(
		_seed
	),
	name_(
		_name
	),
	spawn_boss_{
		_spawn_boss
	},
	grid_(
		_grid
	),
	background_grid_(
		_background_grid
	),
	openings_(
		_openings
	),
	spawns_(
		_spawns
	),
	destructibles_(
		_destructibles
	)
{
}

sanguis::creator::seed
sanguis::creator::top_result::seed() const
{
	return
		seed_;
}

sanguis::creator::name const &
sanguis::creator::top_result::name() const
{
	return
		name_;
}

sanguis::creator::spawn_boss
sanguis::creator::top_result::spawn_boss() const
{
	return
		spawn_boss_;
}

sanguis::creator::grid const &
sanguis::creator::top_result::grid() const
{
	return
		grid_;
}

sanguis::creator::background_grid const &
sanguis::creator::top_result::background_grid() const
{
	return
		background_grid_;
}

sanguis::creator::opening_container_array const &
sanguis::creator::top_result::openings() const
{
	return
		openings_;
}

sanguis::creator::spawn_container const &
sanguis::creator::top_result::spawns() const
{
	return
		spawns_;
}

sanguis::creator::destructible_container const &
sanguis::creator::top_result::destructibles() const
{
	return
		destructibles_;
}
