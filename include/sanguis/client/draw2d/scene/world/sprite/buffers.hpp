#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_BUFFERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_BUFFERS_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/choices.hpp>
#include <sge/sprite/buffers/single_fwd.hpp>
#include <sge/sprite/buffers/with_declaration_fwd.hpp>

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

typedef sge::sprite::buffers::with_declaration<
	sge::sprite::buffers::single<
		sprite::choices
	>
> buffers;

}
}
}
}
}
}

#endif
