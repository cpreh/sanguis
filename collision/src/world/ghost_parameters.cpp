#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/group_field.hpp>


sanguis::collision::world::ghost_parameters::ghost_parameters(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius,
	sanguis::collision::world::body_enter_callback const &_body_enter_callback,
	sanguis::collision::world::body_exit_callback const &_body_exit_callback,
	sanguis::collision::world::group_field const &_collision_groups
)
:
	center_(
		_center
	),
	radius_(
		_radius
	),
	body_enter_callback_(
		_body_enter_callback
	),
	body_exit_callback_(
		_body_exit_callback
	),
	collision_groups_(
		_collision_groups
	)
{
}

sanguis::collision::center const
sanguis::collision::world::ghost_parameters::center() const
{
	return
		center_;
}

sanguis::collision::radius const
sanguis::collision::world::ghost_parameters::radius() const
{
	return
		radius_;
}

sanguis::collision::world::body_enter_callback const &
sanguis::collision::world::ghost_parameters::body_enter_callback() const
{
	return
		body_enter_callback_;
}

sanguis::collision::world::body_exit_callback const &
sanguis::collision::world::ghost_parameters::body_exit_callback() const
{
	return
		body_exit_callback_;
}

sanguis::collision::world::group_field const &
sanguis::collision::world::ghost_parameters::collision_groups() const
{
	return
		collision_groups_;
}
