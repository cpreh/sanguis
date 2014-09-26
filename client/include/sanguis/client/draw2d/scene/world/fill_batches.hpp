#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILL_BATCHES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILL_BATCHES_HPP_INCLUDED

#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/scene/world/fill_batches_base.hpp>
#include <sanguis/client/draw2d/scene/world/is_background.hpp>
#include <sanguis/client/draw2d/scene/world/lower_bound.hpp>
#include <sanguis/client/draw2d/scene/world/tile_size.hpp>
#include <sanguis/client/draw2d/scene/world/to_tile_texture.hpp>
#include <sanguis/client/draw2d/scene/world/upper_bound.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/container.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/dim.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/vector.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
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

template<
	typename Tile
>
sanguis::client::draw2d::scene::world::sprite::container
fill_batches(
	sanguis::client::draw2d::scene::world::sprite::container &&_sprites,
	sanguis::client::draw::debug const _debug,
	sanguis::client::load::tiles::context &_tiles,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::client::draw2d::scene::world::lower_bound const &_lower_bound,
	sanguis::client::draw2d::scene::world::upper_bound const &_upper_bound,
	sanguis::client::draw2d::scene::world::is_background const _is_background
)
{
	return
		sanguis::client::draw2d::scene::world::fill_batches_base(
			std::move(
				_sprites
			),
			_grid,
			_lower_bound,
			_upper_bound,
			_is_background,
			[](
				sanguis::client::draw2d::scene::world::sprite::vector const _pos
			)
			{
				return
					_pos
					-
					fcppt::math::dim::fill<
						sanguis::client::draw2d::scene::world::sprite::dim
					>(
						sanguis::client::draw2d::scene::world::tile_size::value
						/
						fcppt::literal<
							sanguis::client::draw2d::scene::world::sprite::dim::value_type
						>(
							2
						)
					);
			},
			[
				&_tiles,
				&_grid,
				_debug
			](
				sanguis::creator::pos const _pos
			)
			{
				return
					sanguis::client::draw2d::scene::world::to_tile_texture(
						_tiles,
						_debug,
						_grid,
						_pos
					);
			}
		);
}

}
}
}
}
}

#endif
