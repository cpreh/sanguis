#include "create_circle.hpp"
#include "../collision/satellite.hpp"
#include <sge/collision/world.hpp>
#include <sge/math/vector/construct.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <boost/tr1/reference.hpp>

sge::collision::base_ptr const
sanguis::server::entities::create_circle(
	base_parameters const &param,
	collision::base &obj
)
{
	return
		param.env().collision_world()->create_circle(
			sge::collision::satellite_ptr(
				sge::make_auto_ptr<
					collision::satellite
				>(
					std::tr1::ref(
						obj
					)
				)
			),
			sge::math::vector::construct(
				param.center(),
				static_cast<
					space_unit
				>(0)
			),
			sge::math::vector::construct(
				angle_to_vector(
					param.direction() // TODO: is this right?
				) * param.properties()[
					property_type::movement_speed
				].current(),
				static_cast<
					space_unit
				>(0)
			),
			static_cast<sge::collision::unit>(
				entities::radius(
					param.collision_dim()
				)
			)
		);
}
