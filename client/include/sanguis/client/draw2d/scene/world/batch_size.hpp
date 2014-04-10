#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_SIZE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_SIZE_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
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

typedef std::integral_constant<
	sanguis::creator::size_type,
	16
> batch_size;

}
}
}
}
}

#endif
