#include "collision.hpp"
#include "bounding_circle.hpp"
#include "entities/entity.hpp"
#include <sge/math/circle_impl.hpp>

bool sanguis::server::collides(
	entities::entity const &a,
	entities::entity const &b)
{
	return sge::math::intersects(
		bounding_circle(a),
		bounding_circle(b));
}

bool sanguis::server::collides(
	entities::entity const &a,
	messages::circle_type const &c)
{
	return sge::math::intersects(
		bounding_circle(a),
		c);
}
