#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_SYSTEM_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_SYSTEM_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/choices.hpp>
#include <sge/sprite/system.hpp>

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

typedef sge::sprite::system<
	sprite::choices
>::type system;

}
}
}
}
}
}

#endif
