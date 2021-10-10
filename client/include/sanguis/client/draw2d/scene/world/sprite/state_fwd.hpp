#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_STATE_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_STATE_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/state_choices_fwd.hpp>
#include <sge/sprite/state/object_fwd.hpp>

namespace sanguis::client::draw2d::scene::world::sprite
{

using state =
    sge::sprite::state::object<sanguis::client::draw2d::scene::world::sprite::state_choices>;

}

#endif
