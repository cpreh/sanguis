#include "velocity_from_movement.hpp"
#include "../../../exception.hpp"
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/math/vector/unit_circle.hpp>
#include <fcppt/random/uniform_impl.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::speed const
sanguis::client::draw2d::particle::velocity_from_movement(
	particle::movement_type::type const _movement,
	draw2d::center const &_refpoint,
	particle::uniform_rotation &_velocity_angle,
	particle::uniform_velocity_range &_velocity_value
)
{
	switch(
		_movement
	)
	{
		case movement_type::random:
			return
				draw2d::speed(
					fcppt::math::vector::unit_circle(
						_velocity_angle()
					)
					* _velocity_value()
				);
		case movement_type::shrinking:
			return
				draw2d::speed(
					fcppt::math::vector::normalize(
						_refpoint.get()
					)
				);
		case movement_type::expanding:
			return
				draw2d::speed(
					fcppt::math::vector::normalize(
						-_refpoint.get()
					)
				);
		case movement_type::size:
			break;
	}

	throw sanguis::exception(
		FCPPT_TEXT("invalid movement type")
	);
}
