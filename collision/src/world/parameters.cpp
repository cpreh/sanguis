#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/creator/dim.hpp>


sanguis::collision::world::parameters::parameters(
	sanguis::creator::dim const _grid_size
)
:
	grid_size_(
		_grid_size
	)
{
}

sanguis::creator::dim
sanguis::collision::world::parameters::grid_size() const
{
	return
		grid_size_;
}
