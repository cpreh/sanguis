#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_STATE_HPP_INCLUDED

#include <sge/sprite/state/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/state_choices.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{
namespace sprite
{

typedef sge::sprite::state::object<
	sanguis::client::draw2d::scene::world::sprite::state_choices
> state;

}
}
}
}
}
}

#endif
