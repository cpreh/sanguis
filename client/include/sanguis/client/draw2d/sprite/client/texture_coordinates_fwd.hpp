#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_TEXTURE_COORDINATES_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_TEXTURE_COORDINATES_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices.hpp>
#include <sge/sprite/types/texture_coordinates_fwd.hpp>


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

typedef sge::sprite::types::texture_coordinates<
	sanguis::client::draw2d::sprite::type_choices
> texture_coordinates;

}
}
}
}
}

#endif
