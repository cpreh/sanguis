#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_SIZE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_SIZE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/unit.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/mpl/integral_cast.hpp>


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

typedef fcppt::mpl::integral_cast<
	sanguis::client::draw2d::scene::world::sprite::unit,
	sanguis::creator::tile_size
>::type tile_size;

}
}
}
}
}

#endif
