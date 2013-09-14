#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/aux_/world/simple/body.hpp>
#include <sanguis/collision/aux_/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_parameters.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/collision/world/position_change_callback.hpp>


sanguis::collision::aux_::world::simple::body::body(
	sanguis::collision::world::body_parameters const &_parameters,
	sanguis::collision::aux_::world::simple::body_remove_callback const &_body_remove_callback
)
:
	sanguis::collision::world::body(),
	body_remove_callback_(
		_body_remove_callback
	),
	position_change_callback_(
		_parameters.position_change_callback()
	),
	radius_(
		_parameters.radius()
	),
	collision_groups_(
		_parameters.collision_groups()
	),
	body_base_(
		_parameters.body_base()
	),
	center_(
		_parameters.center()
	),
	speed_(
		_parameters.speed()
	)
{
}

sanguis::collision::aux_::world::simple::body::~body()
{
	body_remove_callback_(
		*this
	);
}

void
sanguis::collision::aux_::world::simple::body::center(
	sanguis::collision::center const _center
)
{
	center_ =
		_center;

	position_change_callback_(
		this->center()
	);
}

sanguis::collision::center const
sanguis::collision::aux_::world::simple::body::center() const
{
	return
		center_;
}

void
sanguis::collision::aux_::world::simple::body::speed(
	sanguis::collision::speed const _speed
)
{
	speed_ =
		_speed;
}

sanguis::collision::speed const
sanguis::collision::aux_::world::simple::body::speed() const
{
	return
		speed_;
}

sanguis::collision::radius const
sanguis::collision::aux_::world::simple::body::radius() const
{
	return
		radius_;
}

sanguis::collision::world::group_field const
sanguis::collision::aux_::world::simple::body::collision_groups() const
{
	return
		collision_groups_;
}

sanguis::collision::world::body_base &
sanguis::collision::aux_::world::simple::body::body_base() const
{
	return
		body_base_;
}
