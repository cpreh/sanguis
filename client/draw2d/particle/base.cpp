#include "base.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>

sanguis::client::draw2d::particle::base::base(
	point const &pos_,
	point const &vel_,
	depth_type depth_,
	rotation_type rot_,
	rotation_type rot_vel_,
)
:
	pos_(pos_),
	vel_(vel_),
	depth_(depth_),
	rot_(rot_),
	rot_vel_(rot_vel_)
{}

sanguis::client::draw2d::particle::base::~base()
{}

bool sanguis::client::draw2d::particle::base::update(
	time_type const delta,
	point const &,
	rotation_type,
	depth_type)
{
	pos(pos() + vel() * delta);
	rot(rot() + rot_vel() * delta);
	return false;
}

void sanguis::client::draw2d::particle::base::pos(
	point const &p)
{
	pos_ = p;
}

void sanguis::client::draw2d::particle::base::vel(
	point const &p)
{
	vel_ = p;
}

void sanguis::client::draw2d::particle::base::depth(
	depth_type const p)
{
	depth_ = p;
}

void sanguis::client::draw2d::particle::base::rot(
	rotation_type const p)
{
	rot_ = p;
}

void sanguis::client::draw2d::particle::base::rot_vel(
	rotation_type const p)
{
	rot_vel_ = p;
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
