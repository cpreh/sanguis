#include "clamp_orientation.hpp"
#include <fcppt/math/mod.hpp>
#include <fcppt/math/twopi.hpp>
#include <cmath>

sanguis::client::draw2d::sprite::rotation_type
sanguis::client::draw2d::entities::model::clamp_orientation(
	sprite::rotation_type const _orientation
)
{
	sprite::rotation_type const twopi(
		fcppt::math::twopi<
			sprite::rotation_type
		>()
	);

	sprite::rotation_type const clamped(
		fcppt::math::mod(
			_orientation,
			twopi
		)
	);

	return
		clamped < 0
		?
			clamped
			+ twopi
		:
			clamped;
}
