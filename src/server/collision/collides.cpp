#include "collides.hpp"
#include "bounding_circle.hpp"
#include "../entities/base.hpp"
#include <fcppt/math/sphere/basic_impl.hpp>
#include <fcppt/math/sphere/intersects.hpp>

bool
sanguis::server::collision::collides(
	entities::base const &_a,
	entities::base const &_b
)
{
	return
		fcppt::math::sphere::intersects(
			collision::bounding_circle(
				_a
			),
			collision::bounding_circle(
				_b
			)
		);
}

bool
sanguis::server::collision::collides(
	entities::base const &_entity,
	server::circle const &_circle
)
{
	return
		fcppt::math::sphere::intersects(
			collision::bounding_circle(
				_entity
			),
			_circle
		);
}
