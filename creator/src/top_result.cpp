#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/top_result.hpp>


sanguis::creator::top_result::top_result(
	sanguis::creator::seed const _seed,
	sanguis::creator::name const _name,
	sanguis::creator::grid const &_grid,
	sanguis::creator::opening_container const &_openings,
	sanguis::creator::spawn_container const &_spawns
)
:
	seed_(
		_seed
	),
	name_(
		_name
	),
	grid_(
		_grid
	),
	openings_(
		_openings
	),
	spawns_(
		_spawns
	)
{
}

sanguis::creator::seed const
sanguis::creator::top_result::seed() const
{
	return seed_;
}

sanguis::creator::name const
sanguis::creator::top_result::name() const
{
	return name_;
}

sanguis::creator::grid const &
sanguis::creator::top_result::grid() const
{
	return grid_;
}

sanguis::creator::opening_container const &
sanguis::creator::top_result::openings() const
{
	return openings_;
}

sanguis::creator::spawn_container const &
sanguis::creator::top_result::spawns() const
{
	return spawns_;
}
