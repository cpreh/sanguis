#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_BATCH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_BATCH_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/batch_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>

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

world::batch const
make_batch(
	sge::renderer::device::core &,
	sge::renderer::vertex_declaration const &,
	load::resource::textures const &,
	sanguis::creator::geometry::shape_container
);

}
}
}
}
}

#endif
