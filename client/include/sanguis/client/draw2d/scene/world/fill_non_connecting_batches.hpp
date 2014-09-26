#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILL_NON_CONNECTING_BATCHES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILL_NON_CONNECTING_BATCHES_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/debug.hpp>
#include <sanguis/client/draw2d/scene/world/lower_bound.hpp>
#include <sanguis/client/draw2d/scene/world/upper_bound.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/container.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>


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

sanguis::client::draw2d::scene::world::sprite::container
fill_non_connecting_batches(
	sanguis::client::draw2d::scene::world::sprite::container &&,
	sanguis::client::draw2d::scene::world::debug const _debug,
	sanguis::client::load::tiles::context &,
	sanguis::creator::grid const &,
	sanguis::client::draw2d::scene::world::lower_bound const &,
	sanguis::client::draw2d::scene::world::upper_bound const &
);

}
}
}
}
}

#endif
