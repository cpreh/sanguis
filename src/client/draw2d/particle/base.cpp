#include "base.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>

sanguis::client::draw2d::particle::base::base(
	draw2d::center const &_center,
	draw2d::speed const &_speed,
	particle::depth const _depth,
	particle::rotation const _rot,
	particle::rotation_speed const _rot_speed
)
:
	center_(_center),
	speed_(_speed),
	depth_(_depth),
	rot_(_rot),
	rot_speed_(_rot_speed)
{
}

sanguis::client::draw2d::particle::base::~base()
{
}

bool
sanguis::client::draw2d::particle::base::update(
	time_type const _delta,
	draw2d::center const &,
	particle::rotation,
	particle::depth
)
{
	this->center(
		draw2d::center(
			this->center().get()
			+
			this->speed().get()
			*
			_delta
		)
	);

	this->rot(
		particle::rotation(
			this->rot().get()
			+
			this->rot_speed().get()
			*
			_delta
		)
	);

	return false;
}

void
sanguis::client::draw2d::particle::base::center(
	draw2d::center const &_center
)
{
	center_ = _center;
}

void
sanguis::client::draw2d::particle::base::speed(
	draw2d::speed const &_speed
)
{
	speed_ = _speed;
}

void
sanguis::client::draw2d::particle::base::depth(
	particle::depth const _depth
)
{
	depth_ = _depth;
}

void
sanguis::client::draw2d::particle::base::rot(
	particle::rotation const _rot
)
{
	rot_ = _rot;
}

void
sanguis::client::draw2d::particle::base::rot_speed(
	particle::rotation_speed const _rot_speed
)
{
	rot_speed_ = _rot_speed;
}

sanguis::client::draw2d::center const &
sanguis::client::draw2d::particle::base::center() const
{
	return center_;
}

sanguis::client::draw2d::speed const &
sanguis::client::draw2d::particle::base::speed() const
{
	return speed_;
}

sanguis::client::draw2d::particle::depth const &
sanguis::client::draw2d::particle::base::depth() const
{
	return depth_;
}

sanguis::client::draw2d::particle::rotation const &
sanguis::client::draw2d::particle::base::rot() const
{
	return rot_;
}

sanguis::client::draw2d::particle::rotation_speed const &
sanguis::client::draw2d::particle::base::rot_speed() const
{
	return rot_speed_;
}
