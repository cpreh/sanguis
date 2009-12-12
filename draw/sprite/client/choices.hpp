#ifndef SANGUIS_DRAW_SPRITE_CLIENT_CHOICES_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_CLIENT_CHOICES_HPP_INCLUDED

#include "type_choices.hpp"
#include <sge/sprite/choices.hpp>
#include <sge/sprite/with_repetition.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/with_visibility.hpp>
#include <sge/sprite/intrusive/tag.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace draw
{
namespace sprite
{
namespace client
{

typedef sge::sprite::choices<
	type_choices,
	boost::mpl::vector4<
		sge::sprite::with_repetition,
		sge::sprite::with_texture,
		sge::sprite::with_visibility,
		sge::sprite::intrusive::tag
	>
> choices;

}
}
}
}

#endif
