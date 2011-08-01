#include "container.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/point_rotate.hpp>
#include <fcppt/math/compare.hpp>

sanguis::client::draw2d::particle::container::container(
	sanguis::diff_clock const &_diff_clock,
	draw2d::center const &_center,
	draw2d::speed const &_speed,
	particle::depth const _depth,
	particle::rotation const _rot,
	particle::rotation_speed const _rot_speed
)
:
	particle::base(
		_diff_clock,
		_center,
		_speed,
		_depth,
		_rot,
		_rot_speed
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
	particle::base_ptr _ptr
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
	draw2d::center const &_center,
	particle::rotation const _rot,
	particle::depth const _depth
)
{
	base::update(
		_center,
		_rot,
		_depth
	);

	draw2d::center const this_center(
		fcppt::math::point_rotate(
			(_center + base::center()).get(),
			_center.get(),
			(_rot + base::rot()).get()
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
				this_center,
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
