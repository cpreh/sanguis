#include "container.hpp"
#include <sge/math/point_rotate.hpp>
#include <sge/math/compare.hpp>
#include <boost/foreach.hpp>

sanguis::draw::particle::container::container(
	point const &p,
	point const &v,
	depth_type const depth_,
	rotation_type const rot_,
	rotation_type const rot_vel_)
:
	base(
		p,
		v,
		depth_,
		rot_,
		rot_vel_)
{}

void sanguis::draw::particle::container::add(
	base_ptr ptr)
{
	children_.push_back(ptr);
}

void sanguis::draw::particle::container::gather(
	point const &p,
	rotation_type const r,
	depth_type const d,
	sge::sprite::system::container &sprites) const
{
	point const thispos = sge::math::point_rotate(
		p+base::pos(),
		p,
		r+base::rot());

	BOOST_FOREACH(base const &b,children())
		b.gather(
			thispos,
			r+base::rot(),
			d+base::depth(),
			sprites);
}

bool sanguis::draw::particle::container::update(
	time_type const delta)
{
	base::update(delta);

	for (children_container::iterator i = children().begin(); 
	     i != children().end(); 
		 )
	{
		if (i->update(delta))
		{
			i = children().erase(i);
			continue;
		}
		++i;
	}

	return children().empty();
}
