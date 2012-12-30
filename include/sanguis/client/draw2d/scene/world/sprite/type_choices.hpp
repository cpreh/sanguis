#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_TYPE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_TYPE_CHOICES_HPP_INCLUDED

#include <sanguis/creator/geometry/unit.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
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

typedef sge::sprite::config::type_choices<
	sge::sprite::config::unit_type<
		std::make_signed<
			sanguis::creator::geometry::unit
		>::type
	>,
	sge::sprite::config::float_type<
		float // don't care
	>
> type_choices;

}
}
}
}
}
}

#endif
