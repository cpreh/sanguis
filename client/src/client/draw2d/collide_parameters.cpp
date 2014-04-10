#include <sanguis/duration.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/dim2.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/collide_parameters.hpp>


sanguis::client::draw2d::collide_parameters::collide_parameters(
	sanguis::duration const _duration,
	sanguis::client::draw2d::center const _center,
	sanguis::client::draw2d::speed const _speed,
	sanguis::client::draw2d::dim2 const _size
)
:
	duration_(
		_duration
	),
	center_(
		_center
	),
	speed_(
		_speed
	),
	size_(
		_size
	)
{
}

sanguis::duration const
sanguis::client::draw2d::collide_parameters::duration() const
{
	return
		duration_;
}

sanguis::client::draw2d::center const
sanguis::client::draw2d::collide_parameters::center() const
{
	return
		center_;
}

sanguis::client::draw2d::speed const
sanguis::client::draw2d::collide_parameters::speed() const
{
	return
		speed_;
}

sanguis::client::draw2d::dim2 const
sanguis::client::draw2d::collide_parameters::size() const
{
	return
		size_;
}
