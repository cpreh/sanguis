#ifndef SANGUIS_SERVER_WORLD_TRIANGLE_TRAITS_ACCESS_ELEMENT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_TRIANGLE_TRAITS_ACCESS_ELEMENT_HPP_INCLUDED

#include <sanguis/creator/geometry/unit.hpp>
#include <sanguis/creator/geometry/vector.hpp>
#include <sanguis/creator/geometry/vertex.hpp>
#include <sanguis/server/world/triangle_traits/tag.hpp>
#include <sge/projectile/triangulation/traits/access_element_fwd.hpp>


namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace traits
{

template<>
struct access_element<
	sanguis::creator::geometry::vertex,
	sanguis::server::world::triangle_traits::tag
>
{
	static
	inline
	sanguis::creator::geometry::unit
	execute(
		sanguis::creator::geometry::vertex const &_vertex,
		sanguis::creator::geometry::vector::size_type const _index
	)
	{
		return
			_vertex.pos()[
				_index
			];
	}
};

}
}
}
}

#endif
