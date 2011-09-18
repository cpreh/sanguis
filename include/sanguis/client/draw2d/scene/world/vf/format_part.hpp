#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_FORMAT_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_FORMAT_PART_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/vf/pos.hpp>
#include <sanguis/client/draw2d/scene/world/vf/texpos.hpp>
#include <sge/renderer/vf/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

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

typedef sge::renderer::vf::part<
	boost::mpl::vector2<
		vf::pos,
		vf::texpos
	>
> format_part;

}
}
}
}
}
}

#endif
