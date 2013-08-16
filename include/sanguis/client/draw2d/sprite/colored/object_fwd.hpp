#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_OBJECT_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_OBJECT_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/colored/choices_fwd.hpp>
#include <sge/sprite/object_fwd.hpp>


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

typedef sge::sprite::object<
	sanguis::client::draw2d::sprite::colored::choices
> object;

}
}
}
}
}

#endif
