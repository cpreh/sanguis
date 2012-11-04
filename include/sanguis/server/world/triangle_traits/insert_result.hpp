#ifndef SANGUIS_SERVER_WORLD_TRIANGLE_TRAITS_INSERT_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_TRIANGLE_TRAITS_INSERT_RESULT_HPP_INCLUDED

#include <sanguis/creator/geometry/vertex_fwd.hpp>
#include <sanguis/server/world/convert_vertex.hpp>
#include <sanguis/server/world/triangle_traits/tag.hpp>
#include <sge/projectile/triangle.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/triangulation/traits/insert_result_fwd.hpp>


namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace traits
{

template<>
struct insert_result<
	sge::projectile::shape::triangle_sequence,
	sanguis::creator::geometry::vertex,
	sanguis::server::world::triangle_traits::tag
>
{
	static
	inline
	void
	execute(
		sge::projectile::shape::triangle_sequence &_triangles,
		sanguis::creator::geometry::vertex const &_v1,
		sanguis::creator::geometry::vertex const &_v2,
		sanguis::creator::geometry::vertex const &_v3
	)
	{
		sge::projectile::triangle const result =
		{{
			sanguis::server::world::convert_vertex(
				_v1
			),
			sanguis::server::world::convert_vertex(
				_v2
			),
			sanguis::server::world::convert_vertex(
				_v3
			)
		}};

		_triangles.push_back(
			result
		);
	}
};

}
}
}
}

#endif
