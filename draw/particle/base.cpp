#include "base.hpp"

sanguis::draw::particle::base::base(
	point const &pos_,
	point const &vel_,
	depth_type depth_,
	rotation_type rot_,
	rotation_type rot_vel_)
:
	pos_(pos_),
	vel_(vel_),
	depth_(depth_),
	rot_(rot_),
	rot_vel_(rot_vel_)
{
}

sanguis::draw::particle::base::~base()
{}

bool sanguis::draw::particle::base::update(
	time_type const delta)
{
	pos(pos() + vel()*delta);
	rot(rot() + rot_vel()*delta);
	return false;
}
