#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_SIZE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_SIZE_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/size_fwd.hpp>


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

sanguis::creator::pos
clamp_size(
	sanguis::creator::pos const &,
	sanguis::creator::size const &
);

}
}
}
}
}

#endif
