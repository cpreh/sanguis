#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_STATE_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_STATE_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/state_choices_fwd.hpp>
#include <sge/sprite/state/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

using
state
=
sge::sprite::state::object<
	sanguis::client::draw2d::sprite::state_choices
>;

}
}
}
}

#endif
