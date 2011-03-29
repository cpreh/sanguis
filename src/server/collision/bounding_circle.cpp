#include "bounding_circle.hpp"
#include "../entities/base.hpp"
#include <fcppt/math/sphere/basic_impl.hpp>

sanguis::server::circle const
sanguis::server::collision::bounding_circle(
	entities::base const &_entity
)
{
	return
		server::circle(
			_entity.center(),
			_entity.radius() * static_cast<server::space_unit>(0.7)
		);
}
