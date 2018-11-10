#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_SYSTEM_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_SYSTEM_DECL_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/choices.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>


extern
template
class
sanguis::client::draw2d::sprite::system<
	sanguis::client::draw2d::sprite::normal::choices,
	sanguis::client::draw2d::z_ordering
>;

#endif
