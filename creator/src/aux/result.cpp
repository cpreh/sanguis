#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/aux/result.hpp>


sanguis::creator::aux::result::result(
	sanguis::creator::grid const &_grid,
	sanguis::creator::opening_container const &_openings
)
:
	grid_(
		_grid
	),
	openings_(
		_openings
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
