#include "collides.hpp"
#include "bounding_circle.hpp"
#include "../entities/base.hpp"
#include <fcppt/math/sphere/basic_impl.hpp>
#include <fcppt/math/sphere/intersects.hpp>

bool
sanguis::server::collision::collides(
	entities::base const &a,
	entities::base const &b
)
{
	return intersects(
		bounding_circle(a),
		bounding_circle(b)
	);
}

bool
sanguis::server::collision::collides(
	entities::base const &a,
	circle_type const &c
)
{
	return intersects(
		bounding_circle(a),
		c
	);
}
