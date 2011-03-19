#include "velocity_from_movement.hpp"
#include "rotation.hpp"
#include "../../../exception.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/random/uniform_impl.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::particle::point const
sanguis::client::draw2d::particle::velocity_from_movement(
	movement_type::type const _movement,
	point const &_refpoint,
	uniform_rotation &_velocity_angle,
	uniform_velocity_range &_velocity_value
)
{
	switch(
		_movement
	)
	{
		case movement_type::random:
		{
			rotation const s_angle(
				_velocity_angle()
			);

			return
				particle::point(
					std::cos(s_angle),
					std::sin(s_angle)
				)
				* _velocity_value();
		}
		case movement_type::shrinking:
			return
				fcppt::math::vector::normalize(
					_refpoint
				);
		case movement_type::expanding:
			return
				fcppt::math::vector::normalize(
					-_refpoint
				);
		case movement_type::size:
			break;
	}

	throw sanguis::exception(
		FCPPT_TEXT("invalid movement type")
	);
}
