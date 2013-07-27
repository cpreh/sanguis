#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/aux/result.hpp>


sanguis::creator::aux::result::result(
	sanguis::creator::grid const &_grid,
	sanguis::creator::opening_container const &_openings,
	sanguis::creator::spawn_container const &_spawns
)
:
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

sanguis::creator::grid const &
sanguis::creator::aux::result::grid() const
{
	return grid_;
}

sanguis::creator::opening_container const &
sanguis::creator::aux::result::openings() const
{
	return openings_;
}

sanguis::creator::spawn_container const &
sanguis::creator::aux::result::spawns() const
{
	return spawns_;
}
