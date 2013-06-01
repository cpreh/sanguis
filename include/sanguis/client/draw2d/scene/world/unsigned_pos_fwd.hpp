#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_UNSIGNED_POS_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_UNSIGNED_POS_FWD_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/container/grid/dim_fwd.hpp>


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
	sanguis::creator::size_type,
	2
>::type unsigned_pos;

}
}
}
}
}

#endif
