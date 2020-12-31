#include <sanguis/duration.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/collide_parameters.hpp>
#include <sanguis/client/draw2d/fradius.hpp>
#include <sanguis/client/draw2d/speed.hpp>


sanguis::client::draw2d::collide_parameters::collide_parameters(
	sanguis::duration const _duration,
	sanguis::client::draw2d::center const _center,
	sanguis::client::draw2d::speed const _speed,
	sanguis::client::draw2d::fradius const _radius
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
	radius_(
		_radius
	)
{
}

sanguis::duration
sanguis::client::draw2d::collide_parameters::duration() const
{
	return
		duration_;
}

sanguis::client::draw2d::center
sanguis::client::draw2d::collide_parameters::center() const
{
	return
		center_;
}

sanguis::client::draw2d::speed
sanguis::client::draw2d::collide_parameters::speed() const
{
	return
		speed_;
}

sanguis::client::draw2d::fradius
sanguis::client::draw2d::collide_parameters::radius() const
{
	return
		radius_;
}
