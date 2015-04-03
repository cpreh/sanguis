#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/impl/world/simple/body.hpp>
#include <sanguis/collision/impl/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters.hpp>


sanguis::collision::impl::world::simple::body::body(
	sanguis::collision::world::body_parameters const &_parameters,
	sanguis::collision::impl::world::simple::body_remove_callback const &_body_remove_callback,
	sanguis::collision::impl::world::simple::body_move_callback const &_body_move_callback
)
:
	sanguis::collision::world::body(),
	body_remove_callback_(
		_body_remove_callback
	),
	body_move_callback_(
		_body_move_callback
	),
	radius_(
		_parameters.radius()
	),
	collision_group_(
		_parameters.collision_group()
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

sanguis::collision::impl::world::simple::body::~body()
{
	body_remove_callback_.get()(
		*this
	);
}

void
sanguis::collision::impl::world::simple::body::center(
	sanguis::collision::center const _center
)
{
	this->move(
		_center
	);

	body_move_callback_.get()(
		*this
	);
}

void
sanguis::collision::impl::world::simple::body::move(
	sanguis::collision::center const _center
)
{
	center_ =
		_center;

	body_base_.center_changed(
		_center
	);
}

sanguis::collision::center const
sanguis::collision::impl::world::simple::body::center() const
{
	return
		center_;
}

void
sanguis::collision::impl::world::simple::body::speed(
	sanguis::collision::speed const _speed
)
{
	speed_ =
		_speed;
}

sanguis::collision::speed const
sanguis::collision::impl::world::simple::body::speed() const
{
	return
		speed_;
}

sanguis::collision::radius const
sanguis::collision::impl::world::simple::body::radius() const
{
	return
		radius_;
}

sanguis::collision::world::body_group
sanguis::collision::impl::world::simple::body::collision_group() const
{
	return
		collision_group_;
}

sanguis::collision::world::body_base &
sanguis::collision::impl::world::simple::body::body_base() const
{
	return
		body_base_;
}
