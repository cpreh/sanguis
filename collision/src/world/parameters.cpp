#include <sanguis/collision/world/body_collision_callback.hpp>
#include <sanguis/collision/world/parameters.hpp>


sanguis::collision::world::parameters::parameters(
	sanguis::collision::world::body_collision_callback const &_body_collision_callback
)
:
	body_collision_callback_(
		_body_collision_callback
	)
{
}

sanguis::collision::world::body_collision_callback const &
sanguis::collision::world::parameters::body_collision_callback() const
{
	return
		body_collision_callback_;
}
