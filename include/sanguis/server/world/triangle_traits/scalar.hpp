#ifndef SANGUIS_SERVER_WORLD_TRIANGLE_TRAITS_SCALAR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_TRIANGLE_TRAITS_SCALAR_HPP_INCLUDED

#include <sanguis/creator/geometry/unit.hpp>
#include <sanguis/creator/geometry/vertex.hpp>
#include <sanguis/server/world/triangle_traits/tag.hpp>
#include <sge/projectile/triangulation/traits/scalar_fwd.hpp>


namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace traits
{

template<>
struct scalar<
	sanguis::creator::geometry::vertex,
	sanguis::server::world::triangle_traits::tag
>
{
	typedef sanguis::creator::geometry::unit type;
};

}
}
}
}

#endif
