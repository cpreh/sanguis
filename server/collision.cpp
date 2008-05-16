#include "collision.hpp"
#include "entities/entity.hpp"
#include <sge/math/circle_impl.hpp>
#include <sge/math/power.hpp>
#include <algorithm>

namespace
{

sanguis::messages::circle_type bounding_circle(
	sanguis::server::entities::entity const&);

}

bool sanguis::server::collides(
	entities::entity const& a,
	entities::entity const& b)
{
	return sge::math::intersects(
		bounding_circle(a),
		bounding_circle(b));
}

bool sanguis::server::collides(
	entities::entity const& a,
	messages::circle_type const& c)
{
	return sge::math::intersects(
		bounding_circle(a),
		c);
}

namespace
{

sanguis::messages::circle_type bounding_circle(
	sanguis::server::entities::entity const& e)
{
	return sanguis::messages::circle_type(
		e.center(),
		e.radius());
}

}
