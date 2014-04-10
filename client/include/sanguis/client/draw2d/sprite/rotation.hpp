#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_ROTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_ROTATION_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices.hpp>
#include <sge/sprite/types/rotation.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

typedef sge::sprite::types::rotation<
	sanguis::client::draw2d::sprite::type_choices
> rotation;

}
}
}
}

#endif
