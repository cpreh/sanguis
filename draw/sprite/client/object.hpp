#ifndef SANGUIS_DRAW_SPRITE_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_CLIENT_OBJECT_HPP_INCLUDED

#include "choices.hpp"
#include <sge/sprite/object_fwd.hpp>

namespace sanguis
{
namespace draw
{
namespace sprite
{
namespace client
{

typedef sge::sprite::object<
	choices
> object;

}
}
}
}

#endif
