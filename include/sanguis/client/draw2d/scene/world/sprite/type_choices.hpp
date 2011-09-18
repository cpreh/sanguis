#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_TYPE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_TYPE_CHOICES_HPP_INCLUDED

#include <sanguis/creator/geometry/unit.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/type_choices.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/make_signed.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{
namespace sprite
{

typedef sge::sprite::type_choices<
	boost::make_signed<
		sanguis::creator::geometry::unit
	>::type,
	float, // don't care
	sge::sprite::no_color
> type_choices;

}
}
}
}
}
}

#endif
