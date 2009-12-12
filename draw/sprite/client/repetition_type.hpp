#ifndef SANGUIS_DRAW_SPRITE_CLIENT_REPETITION_TYPE_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_CLIENT_REPETITION_TYPE_HPP_INCLUDED

#include "../float_type.hpp"
#include <sge/sprite/repetition_type.hpp>

namespace sanguis
{
namespace draw
{
namespace sprite
{
namespace client
{

typedef sge::sprite::repetition_type<
	float_type
>::type repetition_type;

}
}
}
}

#endif
