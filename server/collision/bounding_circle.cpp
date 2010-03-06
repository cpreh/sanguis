#include "bounding_circle.hpp"
#include "../entities/base.hpp"
#include <fcppt/math/sphere/basic_impl.hpp>

sanguis::server::circle_type const
sanguis::server::collision::bounding_circle(
	entities::base const &e
)
{
	return circle_type(
		e.center(),
		e.radius() * static_cast<space_unit>(0.7)
	);
}
