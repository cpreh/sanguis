#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SIGNED_POS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SIGNED_POS_HPP_INCLUDED

#include <fcppt/container/grid/dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
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

typedef fcppt::container::grid::dim<
	std::ptrdiff_t,
	2
>::type signed_pos;

}
}
}
}
}

#endif
