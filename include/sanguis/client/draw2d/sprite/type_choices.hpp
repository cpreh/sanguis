#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_TYPE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_TYPE_CHOICES_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

typedef sge::sprite::config::type_choices<
	sge::sprite::config::unit_type<
		sprite::unit
	>,
	sge::sprite::config::float_type<
		sprite::float_unit
	>
> type_choices;

}
}
}
}

#endif
