#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_OBJECT_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_OBJECT_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/client/choices_fwd.hpp>
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
	sanguis::client::draw2d::sprite::client::choices
> object;

}
}
}
}
}

#endif
