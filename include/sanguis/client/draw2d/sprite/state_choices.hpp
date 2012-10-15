#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_STATE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_STATE_CHOICES_HPP_INCLUDED

#include <sge/sprite/state/choices.hpp>
#include <sge/sprite/state/with_blend.hpp>
#include <sge/sprite/state/with_rasterizer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

typedef sge::sprite::state::choices<
	boost::mpl::vector2<
		sge::sprite::state::with_blend,
		sge::sprite::state::with_rasterizer
	>
> state_choices;

}
}
}
}

#endif
