#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GENERATE_BATCHES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GENERATE_BATCHES_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/batch_grid_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers_fwd.hpp>
#include <sanguis/creator/top_parameters_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>


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
	sanguis::creator::top_parameters const &,
	sanguis::load::resource::textures const &,
	sanguis::client::draw2d::scene::world::sprite::buffers &
);

}
}
}
}
}

#endif
