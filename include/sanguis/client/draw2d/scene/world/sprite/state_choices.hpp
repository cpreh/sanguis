#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_STATE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_STATE_CHOICES_HPP_INCLUDED

#include <sge/sprite/state/choices.hpp>
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

typedef sge::sprite::state::choices<
	boost::mpl::vector0<>
> state_choices;

}
}
}
}
}
}

#endif
