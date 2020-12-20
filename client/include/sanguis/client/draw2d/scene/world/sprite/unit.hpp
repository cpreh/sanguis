#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_UNIT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_UNIT_HPP_INCLUDED

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
namespace sprite
{

using
unit
=
std::make_signed_t<
	sanguis::creator::size_type
>;

}
}
}
}
}
}

#endif
