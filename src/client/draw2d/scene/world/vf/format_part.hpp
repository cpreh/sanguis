#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_FORMAT_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_FORMAT_PART_HPP_INCLUDED

#include "pos.hpp"
#include "texpos.hpp"
#include <sge/renderer/vf/part.hpp>
#include <boost/mpl/vector/vector10.hpp>

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
