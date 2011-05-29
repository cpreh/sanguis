#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_CHOICES_HPP_INCLUDED

#include "type_choices.hpp"
#include <sge/sprite/choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <boost/mpl/vector/vector10.hpp>

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

typedef sge::sprite::choices<
	sprite::type_choices,
	boost::mpl::vector1<
		sge::sprite::with_dim
	>
> choices;

}
}
}
}
}
}

#endif
