#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_SIZE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_SIZE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

typedef std::integral_constant<
	sanguis::client::draw2d::scene::world::sprite::unit,
	64
> tile_size;

}
}
}
}
}

#endif
