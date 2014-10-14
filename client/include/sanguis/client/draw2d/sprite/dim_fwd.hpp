#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_DIM_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_DIM_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices.hpp>
#include <sge/sprite/types/dim_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

typedef
sge::sprite::types::dim<
	sanguis::client::draw2d::sprite::type_choices
>
dim;

}
}
}
}

#endif
