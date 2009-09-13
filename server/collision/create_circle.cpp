#include "create_circle.hpp"
#include "../collision/satellite.hpp"
#include "../../angle_to_vector.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/objects/circle.hpp>
#include <sge/math/vector/construct.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/make_auto_ptr.hpp>
#include <boost/tr1/functional.hpp>

sge::collision::objects::base_ptr const
sanguis::server::collision::create_circle(
	sge::collision::world_ptr const collision_world,
	pos_type const &center,
	space_unit const direction,
	space_unit const radius,
	space_unit const movement_speed,
	collision::base &obj
)
{
	return
		collision_world->create_circle(
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
				center,
				static_cast<
					space_unit
				>(0)
			),
			sge::math::vector::construct(
				angle_to_vector(
					direction // TODO: is this right?
				)
				* movement_speed,
				static_cast<
					space_unit
				>(0)
			),
			static_cast<sge::collision::unit>(
				radius
			)
		);
}
