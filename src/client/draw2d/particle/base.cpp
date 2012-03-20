#include <sanguis/client/draw2d/particle/base.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>

sanguis::client::draw2d::particle::base::base(
	sanguis::diff_clock const &_diff_clock,
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
	rot_speed_(_rot_speed),
	diff_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			fcppt::chrono::seconds(
				1
			)
		)
	)
{
}

sanguis::client::draw2d::particle::base::~base()
{
}

bool
sanguis::client::draw2d::particle::base::update(
	draw2d::center const &,
	particle::rotation,
	particle::depth
)
{
	draw2d::funit const diff(
		sge::timer::elapsed_fractional_and_reset<
			draw2d::funit
		>(
			diff_timer_
		)
	);

	this->center(
		draw2d::center(
			this->center().get()
			+
			this->speed().get()
			*
			diff
		)
	);

	this->rot(
		particle::rotation(
			this->rot().get()
			+
			this->rot_speed().get()
			*
			diff
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
