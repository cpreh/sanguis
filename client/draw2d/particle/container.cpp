#include "container.hpp"
#include <fcppt/math/point_rotate.hpp>
#include <fcppt/math/compare.hpp>
#include <boost/foreach.hpp>

sanguis::client::draw2d::particle::container::container(
	point const &p,
	point const &v,
	depth_type const depth_,
	rotation_type const rot_,
	rotation_type const rot_vel_
)
:
	base(
		p,
		v,
		depth_,
		rot_,
		rot_vel_
	)
{}

sanguis::client::draw2d::particle::container::children_container const &
sanguis::client::draw2d::particle::container::children() const
{
	return children_;
}

sanguis::client::draw2d::particle::container::children_container &
sanguis::client::draw2d::particle::container::children()
{
	return children_;
}

void sanguis::client::draw2d::particle::container::add(
	base_ptr ptr)
{
	children_.push_back(ptr);
}

bool sanguis::client::draw2d::particle::container::update(
	time_type const delta,
	point const &p,
	rotation_type const r,
	depth_type const d)
{
	base::update(delta, p, r, d);

	point const thispos = fcppt::math::point_rotate(
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
