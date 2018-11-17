#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/creator/grid_fwd.hpp>


sanguis::collision::world::parameters::parameters(
	sanguis::creator::grid const &_grid
)
:
	grid_(
		_grid
	)
{
}

sanguis::creator::grid const &
sanguis::collision::world::parameters::grid() const
{
	return
		grid_.get();
}
