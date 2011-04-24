#include "clamp_orientation.hpp"
#include <fcppt/math/mod.hpp>
#include <fcppt/math/twopi.hpp>
#include <cmath>

sanguis::client::draw2d::sprite::rotation_type
sanguis::client::draw2d::entities::model::clamp_orientation(
	sprite::rotation_type const _orientation
)
{
	return
		std::abs(
			fcppt::math::mod(
				_orientation,
				fcppt::math::twopi<
					sprite::rotation_type
				>()
			)
		);
}
