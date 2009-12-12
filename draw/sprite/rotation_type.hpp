#ifndef SANGUIS_DRAW_SPRITE_ROTATION_TYPE_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_ROTATION_TYPE_HPP_INCLUDED

#include "float_unit.hpp"
#include <sge/sprite/rotation_type.hpp>

namespace sanguis
{
namespace draw
{
namespace sprite
{

typedef sge::sprite::rotation_type<
	float_unit
>::type rotation_type;

}
}
}

#endif
