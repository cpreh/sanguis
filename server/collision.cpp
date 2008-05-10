#include "collision.hpp"
#include "entities/entity.hpp"
#include <sge/math/circle_impl.hpp>
#include <sge/math/power.hpp>
#include <algorithm>

namespace
{

sge::math::circle bounding_circle(
	sanguis::server::entities::entity const&);

}

bool sanguis::server::collides(
	entities::entity const& a,
	entities::entity const& b)
{
	const sge::math::circle ca(bounding_circle(a)),
	                        cb(bounding_circle(b));
	return (cb.origin() - ca.origin()).length_quad()
	   < ca.radius() + cb.radius();
}

namespace
{

sge::math::circle bounding_circle(
	sanguis::server::entities::entity const& e)
{
	const sanguis::messages::pos_type center(e.center()),
	                                  pos(e.pos());
	// we store the quad of the radius inside the circles
	return sge::math::circle(
		e.center(),
		std::max(
			sge::math::quad(center.x() - pos.x()),
			sge::math::quad(center.y() - pos.y())));
}

}
