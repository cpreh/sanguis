#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_STATE_CHOICES_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_STATE_CHOICES_FWD_HPP_INCLUDED

#include <sge/sprite/state/choices_fwd.hpp>
#include <sge/sprite/state/with_blend_fwd.hpp>
#include <sge/sprite/state/with_rasterizer_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

typedef
sge::sprite::state::choices<
	metal::list<
		sge::sprite::state::with_blend,
		sge::sprite::state::with_rasterizer
	>
>
state_choices;

}
}
}
}

#endif
