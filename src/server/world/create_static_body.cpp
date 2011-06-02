#include "create_static_body.hpp"
#include "../../pixels_per_meter.hpp"
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sanguis/creator/geometry/solidity.hpp>
#include <sanguis/creator/geometry/triangulate/polygon.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/mass.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/object_unique_ptr.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/solid.hpp>
#include <sge/projectile/shape/triangle_mesh.hpp>
#include <sge/projectile/shape/triangle_set.hpp>
#include <sge/projectile/vector2.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>

namespace
{

sge::projectile::vector2::value_type
transform_coords(
	sge::projectile::vector2::value_type const _coord
)
{
	return
		_coord
		/
		static_cast<
			sge::projectile::vector2::value_type
		>(
			sanguis::pixels_per_meter()
		);
}

}

sge::projectile::body::object_unique_ptr
sanguis::server::world::create_static_body(
	sanguis::creator::geometry::shape_container const &_shapes
)
{
	sge::projectile::shape::triangle_set triangles;

	for(
		sanguis::creator::geometry::shape_container::const_iterator shape_it(
			_shapes.begin()
		);
		shape_it != _shapes.end();
		++shape_it
	)
	{
		if(
			shape_it->solidity()
			!=
			sanguis::creator::geometry::solidity::solid
		)
			continue;

		sge::projectile::shape::triangle_set const new_triangles(
			sanguis::creator::geometry::triangulate::polygon<
				sge::projectile::shape::triangle_set
			>(
				shape_it->polygon(),
				transform_coords
			)
		);

		triangles.insert(
			new_triangles.begin(),
			new_triangles.end()
		);
	}

	return
		triangles.empty()
		?
			sge::projectile::body::object_unique_ptr()
		:
			fcppt::make_unique_ptr<
				sge::projectile::body::object
			>(
				sge::projectile::body::parameters(
					sge::projectile::body::position(
						sge::projectile::vector2::null()
					),
					sge::projectile::body::linear_velocity(
						sge::projectile::vector2::null()
					),
					sge::projectile::body::angular_velocity(
						0.f
					),
					fcppt::make_shared_ptr<
						sge::projectile::shape::triangle_mesh
					>(
						triangles
					),
					sge::projectile::body::rotation(
						0.f
					),
					sge::projectile::body::solidity::solid(
						sge::projectile::body::mass(
							1000.f // TODO
						)
					),
					sge::projectile::body::user_data()
				)
			);
}
