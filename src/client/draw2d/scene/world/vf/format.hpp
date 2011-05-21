#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_FORMAT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_FORMAT_HPP_INCLUDED

#include "format_part.hpp"
#include <sge/renderer/vf/format.hpp>
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

typedef sge::renderer::vf::format<
	boost::mpl::vector1<
		vf::format_part
	>
> format;

}
}
}
}
}
}

#endif
