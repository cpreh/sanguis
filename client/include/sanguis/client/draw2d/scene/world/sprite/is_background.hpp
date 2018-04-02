#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_IS_BACKGROUND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_SPRITE_IS_BACKGROUND_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/sprite/is_background_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/is_background_role.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
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

struct is_background
{
	template<
		typename Choices
	>
	struct apply
	{
		typedef
		brigand::list<
			fcppt::record::element<
				sanguis::client::draw2d::scene::world::sprite::is_background_role,
				bool
			>
		>
		type;
	};
};

}
}
}
}
}
}

#endif
