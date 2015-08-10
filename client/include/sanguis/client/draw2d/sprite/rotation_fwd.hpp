#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_ROTATION_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_ROTATION_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices.hpp>
#include <sge/sprite/types/rotation.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::sprite::types::rotation<
		sanguis::client::draw2d::sprite::type_choices
	>,
	rotation
);

}
}
}
}

#endif
