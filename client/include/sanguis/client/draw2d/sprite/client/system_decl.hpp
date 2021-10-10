#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_SYSTEM_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_SYSTEM_DECL_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/client/category.hpp>
#include <sanguis/client/draw2d/sprite/client/choices.hpp>
#include <sanguis/client/draw2d/sprite/client/system_fwd.hpp>

extern template class sanguis::client::draw2d::sprite::system<
    sanguis::client::draw2d::sprite::client::choices,
    sanguis::client::draw2d::sprite::client::category>;

#endif
