#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TRIANGLE_TRAITS_SCALAR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TRIANGLE_TRAITS_SCALAR_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/triangle_traits/tag.hpp>
#include <sanguis/creator/geometry/unit.hpp>
#include <sanguis/creator/geometry/vertex_fwd.hpp>
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
	sanguis::client::draw2d::scene::world::triangle_traits::tag
>
{
	typedef sanguis::creator::geometry::unit type;
};

}
}
}
}

#endif
