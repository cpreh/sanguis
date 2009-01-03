#include "container.hpp"
#include <sge/math/point_rotate.hpp>
#include <sge/math/compare.hpp>
#include <boost/foreach.hpp>

sanguis::draw::particle::container::container(
	point const &p,
	point const &v,
	depth_type const depth_,
	rotation_type const rot_,
	rotation_type const rot_vel_,
	draw::environment const &e)
:
	base(
		p,
		v,
		depth_,
		rot_,
		rot_vel_,
		e)
{}

sanguis::draw::particle::container::children_container const &
sanguis::draw::particle::container::children() const
{
	return children_;
}

sanguis::draw::particle::container::children_container &
sanguis::draw::particle::container::children()
{
	return children_;
}

void sanguis::draw::particle::container::add(
	base_ptr ptr)
{
	children_.push_back(ptr);
}

bool sanguis::draw::particle::container::update(
	time_type const delta,
	point const &p,
	rotation_type const r,
	depth_type const d)
{
	base::update(delta, p, r, d);

	point const thispos = sge::math::point_rotate(
		p + base::pos(),
		p,
		r + base::rot());

	for (children_container::iterator i = children().begin(); 
	     i != children().end(); 
		 )
	{
		if (i->update(
		    	delta,
			thispos,
			r + base::rot(),
			d + base::depth()))
		{
			i = children().erase(i);
			continue;
		}
		++i;
	}

	return children().empty();
}
