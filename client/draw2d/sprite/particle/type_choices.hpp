#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_PARTICLE_TYPE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_PARTICLE_TYPE_CHOICES_HPP_INCLUDED

#include "../unit.hpp"
#include "../float_unit.hpp"
#include <sge/sprite/type_choices.hpp>
#include <sge/image/color/rgba8_format.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace particle
{

typedef sge::sprite::type_choices<
	unit,
	float_unit,
	sge::image::color::rgba8_format
> type_choices;

}
}
}
}
}

#endif
