#include "collides.hpp"
#include "bounding_circle.hpp"
#include "../entities/entity.hpp"
#include <sge/math/circle/basic_impl.hpp>
#include <sge/math/circle/intersects.hpp>

bool sanguis::server::collision::collides(
	entities::entity const &a,
	entities::entity const &b)
{
	return intersects(
		bounding_circle(a),
		bounding_circle(b)
	);
}

bool sanguis::server::collision::collides(
	entities::entity const &a,
	circle_type const &c)
{
	return intersects(
		bounding_circle(a),
		c
	);
}
