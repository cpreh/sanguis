#include "orientation.hpp"
#include <fcppt/math/twopi.hpp>
#include <fcppt/assert.hpp>
#include <algorithm>
#include <cmath>

namespace
{

sanguis::client::draw2d::funit const twopi(
	fcppt::math::twopi<
		sanguis::client::draw2d::funit
	>()
);

void
assert_range(
	sanguis::client::draw2d::sprite::rotation_type
);

}

sanguis::client::draw2d::sprite::rotation_type
sanguis::client::draw2d::entities::model::orientation(
	sanguis::time_type const _time,
	sprite::rotation_type const _orientation,
	sprite::rotation_type const _desired_orientation
)
{
	::assert_range(
		_orientation
	);

	::assert_range(
		_desired_orientation
	);

	// Explanation: we now have the current orientation ('c') and the target ('t')
	// angle on a "line":
	//
	// 0 |--------c------------t------------| 2pi
	// 
	//    ...dist    abs_dist           swap_...
	//
	// The abs_dist below is the "direct" distance from 'c' to 't'. The swap_dist
	// is the distance from 't' to 2pi (the "end") and from there - after
	// wrapping to the origin - to 'c'. Of course, 'c' could also be greater than
	// 't', hence the if test in swap_dist.
	//

	funit const
		// this is the "inner distance" from 
		abs_dist(
			std::abs(
				_desired_orientation - _orientation
			)
		),
		swap_dist(
			(_orientation > _desired_orientation) 
			?
				::twopi - _orientation + _desired_orientation 
			:
				::twopi - _desired_orientation + _orientation
		),
		min_dist(
			std::min(
				swap_dist,
				abs_dist
			)
		);

	FCPPT_ASSERT(
		abs_dist >= static_cast<funit>(0) && 
		swap_dist >= static_cast<funit>(0) && 
		min_dist >= static_cast<funit>(0)
	);

	// We go left or right, depending on:
	//
	// (i) which distance (abs_dist or swap_dist) is smaller
	// (ii) if the current orientation is greater than the target
	funit const dir(
		_orientation > _desired_orientation
		?
			(
				(swap_dist > abs_dist)
				?
					static_cast<funit>(-1)
				:
					static_cast<funit>(1)
			)
		:
			(
				(swap_dist > abs_dist)
				?
					static_cast<funit>(1)
				:
					static_cast<funit>(-1)
			)
	);

	funit const turning_speed(
		fcppt::math::twopi<funit>()
	);

	funit const new_orientation(
		_orientation + dir * _time * turning_speed
	);
	
	// This fixes the "epilepsy" bug. Imagine the current orientation being 10,
	// the desired orientation being 20 and "time" is relatively large in the
	// above assignment. So we might not get orientation values of 15 or 18
	// or 20 in the next frame, but maybe 30. If the next frame is slow again,
	// the orientation is corrected "downwards" to 5 or 10 again, then upwards and
	// so on, causing epilepsy.
	if(
		dir > static_cast<funit>(0)
	)
	{
		if(
			new_orientation < _desired_orientation
		)
			return
				new_orientation;
		else
			return
				_desired_orientation;
	}
	else
	{
		if(
			new_orientation > _desired_orientation
		)
			return
				new_orientation;
		else
			return
				_desired_orientation;
	}
}

namespace
{

void
assert_range(
	sanguis::client::draw2d::sprite::rotation_type const _value
)
{
	FCPPT_ASSERT(
		_value >=
		static_cast<
			sanguis::client::draw2d::funit
		>(
			0
		)
		&& 
		_value <= ::twopi
	);
}

}
