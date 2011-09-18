#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GENERATE_BATCHES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GENERATE_BATCHES_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/batch_grid_unique_ptr.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/creator/generator/top_parameters_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>

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

world::batch_grid_unique_ptr
generate_batches(
	sge::renderer::device &,
	sge::renderer::vertex_declaration const &,
	sanguis::creator::generator::top_parameters const &,
	load::resource::textures const &
);

}
}
}
}
}

#endif
