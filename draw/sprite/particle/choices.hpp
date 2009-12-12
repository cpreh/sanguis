#ifndef SANGUIS_DRAW_SPRITE_PARTICLE_CHOICES_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_PARTICLE_CHOICES_HPP_INCLUDED

#include "type_choices.hpp"
#include <sge/sprite/choices.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_depth.hpp>
#include <sge/sprite/with_rotation.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/intrusive/tag.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace draw
{
namespace sprite
{
namespace particle
{

typedef sge::sprite::choices<
	type_choices,
	boost::mpl::vector5<
		sge::sprite::with_rotation,
		sge::sprite::with_texture,
		sge::sprite::with_depth,
		sge::sprite::with_color,
		sge::sprite::intrusive::tag
	>
> choices;

}
}
}
}

#endif
