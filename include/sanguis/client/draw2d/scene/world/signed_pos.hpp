#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SIGNED_POS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SIGNED_POS_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/container/grid/dim_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
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
	std::make_signed<
		sanguis::creator::size_type
	>::type,
	2
>::type signed_pos;

}
}
}
}
}

#endif
