#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_FORMAT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_VF_FORMAT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/vf/format_part.hpp>
#include <sge/renderer/vf/format.hpp>
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
