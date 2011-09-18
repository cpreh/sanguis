#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_TEXTURE_COORDINATES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_TEXTURE_COORDINATES_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/client/type_choices.hpp>
#include <sge/sprite/texture_coordinates.hpp>

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

typedef sge::sprite::texture_coordinates<
	sprite::client::type_choices::float_type
>::type texture_coordinates;

}
}
}
}
}

#endif
