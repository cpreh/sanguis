#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GENERATE_BATCHES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GENERATE_BATCHES_HPP_INCLUDED

#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers_fwd.hpp>
#include <sanguis/creator/background_grid_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>


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

sanguis::client::draw2d::scene::world::batch_grid
generate_batches(
	sanguis::client::draw::debug,
	sanguis::creator::grid const &,
	sanguis::creator::background_grid const &,
	sanguis::client::load::tiles::context &,
	sanguis::client::draw2d::scene::world::sprite::buffers &
);

}
}
}
}
}

#endif
