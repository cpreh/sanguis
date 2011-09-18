#include <sanguis/client/draw2d/entities/model/clamp_orientation.hpp>
#include <fcppt/math/mod.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::sprite::rotation
sanguis::client::draw2d::entities::model::clamp_orientation(
	sprite::rotation const _orientation
)
{
	sprite::rotation const twopi(
		fcppt::math::twopi<
			sprite::rotation
		>()
	);

	sprite::rotation const clamped(
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
