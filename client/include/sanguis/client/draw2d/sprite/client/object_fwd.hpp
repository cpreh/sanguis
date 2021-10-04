#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_OBJECT_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_OBJECT_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/client/choices_fwd.hpp>
#include <sge/sprite/object_fwd.hpp>


namespace sanguis::client::draw2d::sprite::client
{

using
object
=
sge::sprite::object<
	sanguis::client::draw2d::sprite::client::choices
>;

}

#endif
