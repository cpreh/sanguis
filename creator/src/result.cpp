#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/result.hpp>


sanguis::creator::result::result(
	sanguis::creator::grid const &_grid,
	sanguis::creator::seed const &_seed,
	sanguis::creator::name const &_name
)
:
	grid_(
		_grid
	),
	seed_(
		_seed
	),
	name_(
		_name
	)
{
}

sanguis::creator::grid const &
sanguis::creator::result::grid() const
{
	return grid_;
}

sanguis::creator::seed const
sanguis::creator::result::seed() const
{
	return seed_;
}

sanguis::creator::name const &
sanguis::creator::result::name() const
{
	return name_;
}
