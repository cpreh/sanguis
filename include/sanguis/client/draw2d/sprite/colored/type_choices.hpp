#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_TYPE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_TYPE_CHOICES_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/colored/color_format.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sge/sprite/type_choices.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace colored
{

typedef sge::sprite::type_choices<
	unit,
	float_unit,
	color_format
> type_choices;

}
}
}
}
}

#endif