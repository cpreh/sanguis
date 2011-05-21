#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_BATCH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_BATCH_HPP_INCLUDED

#include "batch_fwd.hpp"
#include "../../../../load/resource/textures_fwd.hpp"
#include <sanguis/creator/geometry/shape_container.hpp>
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

world::batch const
make_batch(
	sge::renderer::device &,
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
