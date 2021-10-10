#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CENTER_TO_GRID_POS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CENTER_TO_GRID_POS_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/creator/pos.hpp>

namespace sanguis::client::draw2d::scene::world
{

sanguis::creator::pos center_to_grid_pos(sanguis::client::draw2d::sprite::center const &);

}

#endif
