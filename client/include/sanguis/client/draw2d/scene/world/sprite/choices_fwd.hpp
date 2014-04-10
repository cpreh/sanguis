#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_CHOICES_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_CHOICES_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/is_background_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/type_choices_fwd.hpp>
#include <sge/sprite/config/choices_fwd.hpp>
#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count_fwd.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/with_texture_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
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

typedef sge::sprite::config::choices<
	sanguis::client::draw2d::scene::world::sprite::type_choices,
	sge::sprite::config::normal_size,
	boost::mpl::vector2<
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			sge::sprite::config::texture_coordinates::automatic,
			sge::sprite::config::texture_ownership::shared
		>,
		sanguis::client::draw2d::scene::world::sprite::is_background
	>
> choices;

}
}
}
}
}
}

#endif
