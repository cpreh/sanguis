#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_SYSTEM_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_SYSTEM_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/client/choices.hpp>
#include <sge/sprite/system.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace client
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
