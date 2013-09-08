#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_parameters.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/collision/world/position_change_callback.hpp>


sanguis::collision::world::body_parameters::body_parameters(
	sanguis::collision::center const _center,
	sanguis::collision::speed const _speed,
	sanguis::collision::radius const _radius,
	sanguis::collision::world::position_change_callback const &_position_change_callback,
	sanguis::collision::world::group_field const &_collision_groups,
	sanguis::collision::world::body_base &_body_base
)
:
	center_(
		_center
	),
	speed_(
		_speed
	),
	radius_(
		_radius
	),
	position_change_callback_(
		_position_change_callback
	),
	collision_groups_(
		_collision_groups
	),
	body_base_(
		_body_base
	)
{
}

sanguis::collision::center const
sanguis::collision::world::body_parameters::center() const
{
	return
		center_;
}

sanguis::collision::speed const
sanguis::collision::world::body_parameters::speed() const
{
	return
		speed_;
}

sanguis::collision::radius const
sanguis::collision::world::body_parameters::radius() const
{
	return
		radius_;
}

sanguis::collision::world::position_change_callback const &
sanguis::collision::world::body_parameters::position_change_callback() const
{
	return
		position_change_callback_;
}

sanguis::collision::world::group_field const &
sanguis::collision::world::body_parameters::collision_groups() const
{
	return
		collision_groups_;
}

sanguis::collision::world::body_base &
sanguis::collision::world::body_parameters::body_base() const
{
	return
		body_base_;
}
