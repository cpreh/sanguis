#include "base.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>

sanguis::draw::particle::base::base(
	point const &pos_,
	point const &vel_,
	depth_type depth_,
	rotation_type rot_,
	rotation_type rot_vel_,
	draw::environment const &e)
:
	pos_(pos_),
	vel_(vel_),
	depth_(depth_),
	rot_(rot_),
	rot_vel_(rot_vel_),
	e(e)
{}

sanguis::draw::particle::base::~base()
{}

bool sanguis::draw::particle::base::update(
	time_type const delta,
	point const &,
	rotation_type,
	depth_type)
{
	pos(pos() + vel() * delta);
	rot(rot() + rot_vel() * delta);
	return false;
}

void sanguis::draw::particle::base::pos(
	point const &p)
{
	pos_ = p;
}

void sanguis::draw::particle::base::vel(
	point const &p)
{
	vel_ = p;
}

void sanguis::draw::particle::base::depth(
	depth_type const p)
{
	depth_ = p;
}

void sanguis::draw::particle::base::rot(
	rotation_type const p)
{
	rot_ = p;
}

void sanguis::draw::particle::base::rot_vel(
	rotation_type const p)
{
	rot_vel_ = p;
}

sanguis::draw::particle::point const &
sanguis::draw::particle::base::pos() const
{
	return pos_;
}

sanguis::draw::particle::point &
sanguis::draw::particle::base::pos()
{
	return pos_;
}

sanguis::draw::particle::point const &
sanguis::draw::particle::base::vel() const
{
	return vel_;
}

sanguis::draw::particle::point &
sanguis::draw::particle::base::vel()
{
	return vel_;
}

sanguis::draw::particle::base::depth_type const &
sanguis::draw::particle::base::depth() const
{
	return depth_;
}

sanguis::draw::particle::base::depth_type &
sanguis::draw::particle::base::depth()
{
	return depth_;
}

sanguis::draw::particle::base::rotation_type const &
sanguis::draw::particle::base::rot() const
{
	return rot_;
}

sanguis::draw::particle::base::rotation_type &
sanguis::draw::particle::base::rot()
{
	return rot_;
}

sanguis::draw::particle::base::rotation_type const &
sanguis::draw::particle::base::rot_vel() const
{
	return rot_vel_;
}

sanguis::draw::particle::base::rotation_type &
sanguis::draw::particle::base::rot_vel()
{
	return rot_vel_;
}

sanguis::draw::environment const &
sanguis::draw::particle::base::environment() const
{
	return e;
}
