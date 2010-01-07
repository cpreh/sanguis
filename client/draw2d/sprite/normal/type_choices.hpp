#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_TYPE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_TYPE_CHOICES_HPP_INCLUDED

#include "../unit.hpp"
#include "../float_unit.hpp"
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
namespace normal
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
