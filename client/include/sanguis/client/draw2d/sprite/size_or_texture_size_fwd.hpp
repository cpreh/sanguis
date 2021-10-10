#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_SIZE_OR_TEXTURE_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_SIZE_OR_TEXTURE_SIZE_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices.hpp>
#include <sge/sprite/types/size_or_texture_size_fwd.hpp>

namespace sanguis::client::draw2d::sprite
{

using size_or_texture_size =
    sge::sprite::types::size_or_texture_size<sanguis::client::draw2d::sprite::type_choices>;

}

#endif
