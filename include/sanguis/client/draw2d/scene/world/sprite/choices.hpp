#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_CHOICES_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/type_choices.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

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

typedef sge::sprite::config::choices<
	sprite::type_choices,
	sge::sprite::config::normal_size,
	boost::mpl::vector0<>
> choices;

}
}
}
}
}
}

#endif
