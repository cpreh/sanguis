#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/entities/model/clamp_orientation.hpp>
#include <sanguis/client/draw2d/entities/model/desired_orientation.hpp>
#include <sanguis/client/draw2d/entities/model/orientation.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cmath>
#include <numbers>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::client::draw2d::sprite::rotation
impl(
	sanguis::client::draw2d::funit const _delta,
	sanguis::client::draw2d::sprite::rotation const _orientation,
	sanguis::client::draw2d::sprite::rotation const _desired_orientation
)
{
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

	auto const twopi(
		std::numbers::pi_v<
			sanguis::client::draw2d::funit
		>
		*
		fcppt::literal<
			sanguis::client::draw2d::funit
		>(
			2
		)
	);

	// this is the "inner distance" from
	sanguis::client::draw2d::funit const abs_dist(
		std::abs(
			_desired_orientation.get()
			-
			_orientation.get()
		)
	);

	sanguis::client::draw2d::funit const swap_dist(
		_orientation
		>
		_desired_orientation
		?
			twopi
			-
			_orientation.get()
			+
			_desired_orientation.get()
		:
			twopi
			-
			_desired_orientation.get()
			+
			_orientation.get()
	);

	sanguis::client::draw2d::funit const min_dist(
		std::min(
			swap_dist,
			abs_dist
		)
	);

	sanguis::client::draw2d::funit const null(
		fcppt::literal<
			sanguis::client::draw2d::funit
		>(
			0
		)
	);

	sanguis::client::draw2d::funit const one(
		fcppt::literal<
			sanguis::client::draw2d::funit
		>(
			1
		)
	);

	sanguis::client::draw2d::funit const minus_one(
		fcppt::literal<
			sanguis::client::draw2d::funit
		>(
			-1
		)
	);

	FCPPT_ASSERT_ERROR(
		abs_dist >= null &&
		swap_dist >= null &&
		min_dist >= null
	);

	// We go left or right, depending on:
	//
	// (i) which distance (abs_dist or swap_dist) is smaller
	// (ii) if the current orientation is greater than the target
	sanguis::client::draw2d::funit const dir(
		_orientation
		>
		_desired_orientation
		?
			(
				swap_dist
				>
				abs_dist
				?
					minus_one
				:
					one
			)
		:
			(
				swap_dist
				>
				abs_dist
				?
					one
				:
					minus_one
			)
	);

	sanguis::client::draw2d::funit const turning_speed(
		twopi
	);

	sanguis::client::draw2d::sprite::rotation const new_orientation(
		_orientation.get()
		+
		dir
		*
		_delta
		*
		turning_speed
	);

	// This fixes the "epilepsy" bug. Imagine the current orientation being 10,
	// the desired orientation being 20 and "time" is relatively large in the
	// above assignment. So we might not get orientation values of 15 or 18
	// or 20 in the next frame, but maybe 30. If the next frame is slow again,
	// the orientation is corrected "downwards" to 5 or 10 again, then upwards and
	// so on, causing epilepsy.
	return
		dir > null
		?
			(
				new_orientation
				<
				_desired_orientation
				?
					new_orientation
				:
					_desired_orientation
			)
		:
			(
				new_orientation
				>
				_desired_orientation
				?
					new_orientation
				:
					_desired_orientation
			)
		;
}

}

sanguis::client::draw2d::sprite::rotation
sanguis::client::draw2d::entities::model::orientation(
	sanguis::client::draw2d::funit const _delta,
	sanguis::client::draw2d::sprite::rotation const _orientation,
	sanguis::client::draw2d::entities::model::desired_orientation const _desired_orientation
)
{
	return
		impl(
			_delta,
			sanguis::client::draw2d::entities::model::clamp_orientation(
				_orientation
			),
			sanguis::client::draw2d::entities::model::clamp_orientation(
				_desired_orientation.get()
			)
		);
}
