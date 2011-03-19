#include "container.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/point_rotate.hpp>
#include <fcppt/math/compare.hpp>
#include <boost/foreach.hpp>

sanguis::client::draw2d::particle::container::container(
	point const &_pos,
	point const &_velocity,
	depth_type const _depth,
	rotation_type const _rot,
	rotation_type const _rot_vel
)
:
	base(
		_pos,
		_velocity,
		_depth,
		_rot,
		_rot_vel
	)
{
}

sanguis::client::draw2d::particle::container::~container()
{
}

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

void
sanguis::client::draw2d::particle::container::add(
	base_ptr _ptr
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		children_,
		move(
			_ptr
		)
	);
}

bool
sanguis::client::draw2d::particle::container::update(
	time_type const _delta,
	point const &_pos,
	rotation_type const _rot,
	depth_type const _depth
)
{
	base::update(
		_delta,
		_pos,
		_rot,
		_depth
	);

	point const thispos(
		fcppt::math::point_rotate(
			_pos + base::pos(),
			_pos,
			_rot + base::rot()
		)
	);

	for(
		children_container::iterator it(
			this->children().begin()
		);
		it !=this-> children().end(); 
	)
	{
		if(
			it->update(
			    	_delta,
				thispos,
				_rot + base::rot(),
				_depth + base::depth()
			)
		)
		{
			it =
				children().erase(
					it
				);

			continue;
		}

		++it;
	}

	return this->children().empty();
}
