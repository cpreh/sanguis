#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_TYPE_CHOICES_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_TYPE_CHOICES_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sge/sprite/config/float_type_fwd.hpp>
#include <sge/sprite/config/type_choices_fwd.hpp>
#include <sge/sprite/config/unit_type_fwd.hpp>


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
		sanguis::client::draw2d::sprite::unit
	>,
	sge::sprite::config::float_type<
		sanguis::client::draw2d::sprite::float_unit
	>
> type_choices;

}
}
}
}

#endif
