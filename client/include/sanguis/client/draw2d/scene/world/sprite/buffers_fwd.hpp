#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_BUFFERS_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_BUFFERS_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/choices_fwd.hpp>
#include <sge/sprite/buffers/multi_fwd.hpp>
#include <sge/sprite/buffers/with_declaration_fwd.hpp>

namespace sanguis::client::draw2d::scene::world::sprite
{

using buffers = sge::sprite::buffers::with_declaration<
    sge::sprite::buffers::multi<sanguis::client::draw2d::scene::world::sprite::choices>>;

}

#endif
