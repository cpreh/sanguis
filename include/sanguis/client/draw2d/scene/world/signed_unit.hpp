#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SIGNED_UNIT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SIGNED_UNIT_HPP_INCLUDED

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

typedef
std::make_signed<
	sanguis::creator::size_type
>::type
signed_unit;

}
}
}
}
}

#endif
