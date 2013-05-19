#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_POS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_POS_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/signed_pos.hpp>


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

sanguis::client::draw2d::scene::world::batch_grid::dim const
clamp_pos(
	sanguis::client::draw2d::scene::world::signed_pos const &,
	sanguis::client::draw2d::scene::world::batch_grid::dim const &
);

}
}
}
}
}

#endif
