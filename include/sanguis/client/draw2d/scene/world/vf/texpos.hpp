#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_TEXPOS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_TEXPOS_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/vf/scalar.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/texpos.hpp>


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
namespace vf
{

typedef sge::renderer::vf::texpos<
	sanguis::client::draw2d::scene::world::vf::scalar,
	2,
	sge::renderer::vf::index<
		0u
	>
> texpos;

}
}
}
}
}
}

#endif
