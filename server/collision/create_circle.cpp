#include "create_circle.hpp"
#include "satellite.hpp"
#include <sge/collision/shapes/sphere.hpp>
#include <sge/collision/world.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

sge::collision::shapes::base_ptr const
sanguis::server::collision::create_circle(
	sge::collision::world_ptr const _world,
	base &_base,
	space_unit const _radius
)
{
	return
		_world->create_sphere(
			sge::collision::satellite_ptr(
				fcppt::make_unique_ptr<
					satellite
				>(
					std::tr1::ref(
						_base
					)
				)
			),
			_radius,
			sge::collision::solidity::nonsolid,
			sge::collision::point::null()
		);
}
