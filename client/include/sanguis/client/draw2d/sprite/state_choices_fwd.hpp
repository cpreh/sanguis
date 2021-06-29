#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_STATE_CHOICES_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_STATE_CHOICES_FWD_HPP_INCLUDED

#include <sge/sprite/state/choices_fwd.hpp>
#include <sge/sprite/state/with_blend_fwd.hpp>
#include <sge/sprite/state/with_rasterizer_fwd.hpp>
#include <fcppt/mpl/list/object.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

using
state_choices
=
sge::sprite::state::choices<
	fcppt::mpl::list::object<
		sge::sprite::state::with_blend,
		sge::sprite::state::with_rasterizer
	>
>;

}
}
}
}

#endif
