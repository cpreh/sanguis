#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_TYPE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_CLIENT_TYPE_CHOICES_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/no_color.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace client
{

typedef sge::sprite::type_choices<
	unit,
	float_unit,
	sge::sprite::no_color
> type_choices;

}
}
}
}
}

#endif