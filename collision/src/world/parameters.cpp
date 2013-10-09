#include <sanguis/collision/world/body_collision_callback.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/creator/dim.hpp>


sanguis::collision::world::parameters::parameters(
	sanguis::collision::world::body_collision_callback const &_body_collision_callback,
	sanguis::creator::dim const _grid_size
)
:
	body_collision_callback_(
		_body_collision_callback
	),
	grid_size_(
		_grid_size
	)
{
}

sanguis::collision::world::body_collision_callback const &
sanguis::collision::world::parameters::body_collision_callback() const
{
	return
		body_collision_callback_;
}

sanguis::creator::dim
sanguis::collision::world::parameters::grid_size() const
{
	return
		grid_size_;
}
