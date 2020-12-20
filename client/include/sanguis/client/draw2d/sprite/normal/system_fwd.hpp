#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_SYSTEM_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_SYSTEM_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/sprite/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/choices_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace normal
{

using
system
=
sanguis::client::draw2d::sprite::system<
	sanguis::client::draw2d::sprite::normal::choices,
	sanguis::client::draw2d::z_ordering
>;

}
}
}
}
}

#endif
