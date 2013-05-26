#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/world/create_static_body.hpp>
#include <sanguis/server/world/make_triangles.hpp>
#include <sge/projectile/vector2.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/object_unique_ptr.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/solid.hpp>
#include <sge/projectile/shape/triangle_mesh.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::projectile::body::object_unique_ptr
sanguis::server::world::create_static_body(
	sanguis::creator::grid const &_tiles
)
{
	sge::projectile::shape::triangle_sequence triangles(
		sanguis::server::world::make_triangles(
			_tiles
		)
	);

	// stupid special case
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
						std::move(
							triangles
						)
					),
					sge::projectile::body::rotation(
						0.f
					),
					sge::projectile::body::solidity::static_(),
					sge::projectile::body::user_data()
				)
			);
}
