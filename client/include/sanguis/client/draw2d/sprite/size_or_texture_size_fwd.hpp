#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_SIZE_OR_TEXTURE_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_SIZE_OR_TEXTURE_SIZE_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices.hpp>
#include <sge/sprite/types/size_or_texture_size_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

typedef
sge::sprite::types::size_or_texture_size<
	sanguis::client::draw2d::sprite::type_choices
>
size_or_texture_size;

}
}
}
}

#endif