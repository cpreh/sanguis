#include "create_circle.hpp"
#include "satellite.hpp"
#include <sge/collision/shapes/sphere.hpp>
#include <sge/collision/world.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_auto_ptr.hpp>

sge::collision::shapes::base_ptr const
sanguis::server::collision::create_circle(
	sge::collision::world_ptr const world_,
	base &base_,
	space_unit const radius_
)
{
	sge::collision::satellite_ptr sat_(
		fcppt::make_auto_ptr<
			satellite
		>(
			std::tr1::ref(
				base_
			)
		)
	);
	
	return
		world_->create_sphere(
			sat_,
			radius_,
			sge::collision::solidity::nonsolid,
			sge::collision::point::null()
		);
}
