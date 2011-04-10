#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_REPETITION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_REPETITION_HPP_INCLUDED

#include "float_unit.hpp"
#include <sge/sprite/repetition_type.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

typedef sge::sprite::repetition_type<
	sprite::float_unit
>::type repetition;

}
}
}
}

#endif
