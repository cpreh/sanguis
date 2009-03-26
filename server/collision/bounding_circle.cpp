#include "bounding_circle.hpp"
#include "../entities/entity.hpp"
#include <sge/math/circle_impl.hpp>

sanguis::server::circle_type const
sanguis::server::collision::bounding_circle(
	entities::entity const &e)
{
	return circle_type(
		e.center(),
		e.radius() * static_cast<space_unit>(0.7));
}
