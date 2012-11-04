#ifndef SANGUIS_SERVER_WORLD_CONVERT_VERTEX_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONVERT_VERTEX_HPP_INCLUDED

#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/creator/geometry/vertex_fwd.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/vector2.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

inline
sge::projectile::vector2 const
convert_vertex(
	sanguis::creator::geometry::vertex const &_vertex
)
{
	sge::projectile::scalar const pixels_per_meter(
		static_cast<
			sge::projectile::scalar
		>(
			sanguis::pixels_per_meter()
		)
	);

	return
		sge::projectile::vector2(
			static_cast<
				sge::projectile::scalar
			>(
				_vertex.pos().x()
			)
			/
			pixels_per_meter
			,
			static_cast<
				sge::projectile::scalar
			>(
				_vertex.pos().y()
			)
			/
			pixels_per_meter
		);
}

}
}
}

#endif
