#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_SIZE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_SIZE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/unit.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/brigand/integral_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed_fun.hpp>


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

typedef
fcppt::brigand::integral_cast<
	sanguis::client::draw2d::scene::world::sprite::unit,
	fcppt::cast::size_fun,
	fcppt::brigand::integral_cast<
		sanguis::creator::difference_type,
		fcppt::cast::to_signed_fun,
		sanguis::creator::tile_size
	>
>
tile_size;

}
}
}
}
}

#endif
