#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GENERATE_BATCHES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GENERATE_BATCHES_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers_ref.hpp>
#include <sanguis/client/load/tiles/context_ref.hpp>
#include <sanguis/creator/background_grid_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


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
	fcppt::log::context_reference,
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::client::draw::debug,
	sanguis::creator::grid const &,
	sanguis::creator::background_grid const &,
	sanguis::client::load::tiles::context_ref,
	sanguis::client::draw2d::scene::world::sprite::buffers_ref
);

}
}
}
}
}

#endif
