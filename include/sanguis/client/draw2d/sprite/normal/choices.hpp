#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_CHOICES_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/normal/type_choices.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_rotation.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/intrusive/tag.hpp>
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
namespace normal
{

typedef sge::sprite::choices<
	type_choices,
	boost::mpl::vector4<
		sge::sprite::with_dim,
		sge::sprite::with_rotation,
		sge::sprite::with_texture,
		sge::sprite::intrusive::tag
	>
> choices;

}
}
}
}
}

#endif
