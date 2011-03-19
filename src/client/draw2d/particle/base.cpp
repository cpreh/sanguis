#include "base.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>

sanguis::client::draw2d::particle::base::base(
	point const &_pos,
	point const &_vel,
	depth_type const _depth,
	rotation_type const _rot,
	rotation_type const _rot_vel
)
:
	pos_(_pos),
	vel_(_vel),
	depth_(_depth),
	rot_(_rot),
	rot_vel_(_rot_vel)
{
}

sanguis::client::draw2d::particle::base::~base()
{
}

bool
sanguis::client::draw2d::particle::base::update(
	time_type const _delta,
	point const &,
	rotation_type,
	depth_type
)
{
	this->pos(
		this->pos()
		+
		this->vel()
		*
		_delta
	);

	this->rot(
		this->rot()
		+
		this->rot_vel()
		*
		_delta
	);

	return false;
}

void
sanguis::client::draw2d::particle::base::pos(
	point const &_pos
)
{
	pos_ = _pos;
}

void
sanguis::client::draw2d::particle::base::vel(
	point const &_vel
)
{
	vel_ = _vel;
}

void
sanguis::client::draw2d::particle::base::depth(
	depth_type const _depth
)
{
	depth_ = _depth;
}

void
sanguis::client::draw2d::particle::base::rot(
	rotation_type const _rot
)
{
	rot_ = _rot;
}

void
sanguis::client::draw2d::particle::base::rot_vel(
	rotation_type const _rot_vel
)
{
	rot_vel_ = _rot_vel;
}

sanguis::client::draw2d::particle::point const &
sanguis::client::draw2d::particle::base::pos() const
{
	return pos_;
}

sanguis::client::draw2d::particle::point &
sanguis::client::draw2d::particle::base::pos()
{
	return pos_;
}

sanguis::client::draw2d::particle::point const &
sanguis::client::draw2d::particle::base::vel() const
{
	return vel_;
}

sanguis::client::draw2d::particle::point &
sanguis::client::draw2d::particle::base::vel()
{
	return vel_;
}

sanguis::client::draw2d::particle::base::depth_type const &
sanguis::client::draw2d::particle::base::depth() const
{
	return depth_;
}

sanguis::client::draw2d::particle::base::depth_type &
sanguis::client::draw2d::particle::base::depth()
{
	return depth_;
}

sanguis::client::draw2d::particle::base::rotation_type const &
sanguis::client::draw2d::particle::base::rot() const
{
	return rot_;
}

sanguis::client::draw2d::particle::base::rotation_type &
sanguis::client::draw2d::particle::base::rot()
{
	return rot_;
}

sanguis::client::draw2d::particle::base::rotation_type const &
sanguis::client::draw2d::particle::base::rot_vel() const
{
	return rot_vel_;
}

sanguis::client::draw2d::particle::base::rotation_type &
sanguis::client::draw2d::particle::base::rot_vel()
{
	return rot_vel_;
}
