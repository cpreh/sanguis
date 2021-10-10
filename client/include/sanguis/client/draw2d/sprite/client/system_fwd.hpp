#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_SYSTEM_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_SYSTEM_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/category_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/choices_fwd.hpp>

namespace sanguis::client::draw2d::sprite::client
{

using system = sanguis::client::draw2d::sprite::system<
    sanguis::client::draw2d::sprite::client::choices,
    sanguis::client::draw2d::sprite::client::category>;

}

#endif
