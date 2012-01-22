#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_OBJECT_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/client/choices.hpp>
#include <sge/sprite/object_fwd.hpp>

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

typedef sge::sprite::object<
	client::choices
> object;

}
}
}
}
}

#endif
