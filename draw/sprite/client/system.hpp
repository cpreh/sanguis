#ifndef SANGUIS_DRAW_SPRITE_CLIENT_SYSTEM_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_CLIENT_SYSTEM_HPP_INCLUDED

#include "choices.hpp"
#include <sge/sprite/system_fwd.hpp>

namespace sanguis
{
namespace draw
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

#endif
