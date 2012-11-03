#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TRIANGLE_TRAITS_INSERT_RESULT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TRIANGLE_TRAITS_INSERT_RESULT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/triangle_traits/tag.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sanguis/creator/geometry/vertex.hpp>
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
	sanguis::creator::geometry::polygon,
	sanguis::creator::geometry::vertex,
	sanguis::client::draw2d::scene::world::triangle_traits::tag
>
{
	static
	inline
	void
	execute(
		sanguis::creator::geometry::polygon &_polygon,
		sanguis::creator::geometry::vertex const &_v1,
		sanguis::creator::geometry::vertex const &_v2,
		sanguis::creator::geometry::vertex const &_v3
	)
	{
		_polygon.push_back(
			_v1
		);

		_polygon.push_back(
			_v2
		);

		_polygon.push_back(
			_v3
		);
	}
};

}
}
}
}

#endif
