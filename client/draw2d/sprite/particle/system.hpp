#ifndef SANGUIS_DRAW_SPRITE_PARTICLE_SYSTEM_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_PARTICLE_SYSTEM_HPP_INCLUDED

#include "choices.hpp"
#include <sge/sprite/system.hpp>

namespace sanguis
{
namespace draw
{
namespace sprite
{
namespace particle
{

typedef sge::sprite::system<
	choices
>::type system;

}
}
}
}

#endif
