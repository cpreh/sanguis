#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_SYSTEM_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_SYSTEM_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/colored/choices.hpp>
#include <sge/sprite/system.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace colored
{

typedef sge::sprite::system<
	choices
>::type system;

}
}
}
}
}

#endif
