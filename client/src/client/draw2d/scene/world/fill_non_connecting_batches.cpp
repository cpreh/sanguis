#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/scene/world/fill_batches_base.hpp>
#include <sanguis/client/draw2d/scene/world/fill_non_connecting_batches.hpp>
#include <sanguis/client/draw2d/scene/world/is_background.hpp>
#include <sanguis/client/draw2d/scene/world/lower_bound.hpp>
#include <sanguis/client/draw2d/scene/world/to_non_connecting_tile_texture.hpp>
#include <sanguis/client/draw2d/scene/world/upper_bound.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/container.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/vector.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::sprite::container
sanguis::client::draw2d::scene::world::fill_non_connecting_batches(
	sanguis::random_generator &_random_generator,
	sanguis::client::draw2d::scene::world::sprite::container &&_sprites,
	sanguis::client::draw::debug const _debug,
	sanguis::client::load::tiles::context &_tiles,
	sanguis::creator::grid const &_grid,
	sanguis::client::draw2d::scene::world::lower_bound const &_lower_bound,
	sanguis::client::draw2d::scene::world::upper_bound const &_upper_bound
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
			sanguis::client::draw2d::scene::world::is_background{
				false
			},
			[](
				sanguis::client::draw2d::scene::world::sprite::vector const _pos
			)
			{
				return
					_pos;
			},
			[
				&_random_generator,
				&_tiles,
				&_grid,
				_debug
			](
				sanguis::creator::pos const _pos
			)
			{
				return
					sanguis::client::draw2d::scene::world::to_non_connecting_tile_texture(
						_random_generator,
						_tiles,
						_debug,
						_grid[
							_pos
						]
					);
			}
		);
}
