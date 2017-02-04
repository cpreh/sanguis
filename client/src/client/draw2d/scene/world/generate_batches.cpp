#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/batch_size.hpp>
#include <sanguis/client/draw2d/scene/world/generate_batches.hpp>
#include <sanguis/client/draw2d/scene/world/make_sprite.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/compare.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/container.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/min.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/sup.hpp>
#include <sanguis/tiles/cell.hpp>
#include <sanguis/tiles/draw.hpp>
#include <sanguis/tiles/log.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/geometry/sort_and_update.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/map.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>


sanguis::client::draw2d::scene::world::batch_grid
sanguis::client::draw2d::scene::world::generate_batches(
	fcppt::log::context &_log_context,
	sanguis::random_generator &_random_generator,
	sanguis::client::draw::debug const _debug,
	sanguis::creator::grid const &_grid,
	sanguis::creator::background_grid const &_background_grid,
	sanguis::client::load::tiles::context &_tiles,
	sanguis::client::draw2d::scene::world::sprite::buffers &_sprite_buffers
)
{
	sanguis::tiles::log const tiles_log{
		_log_context
	};

	sanguis::creator::pos const batch_dim_pos(
		fcppt::math::vector::fill<
			sanguis::creator::pos
		>(
			sanguis::client::draw2d::scene::world::batch_size::value
		)
	);

	return
		sanguis::client::draw2d::scene::world::batch_grid(
			fcppt::math::dim::map(
				_grid.size(),
				[](
					sanguis::creator::grid::dim::value_type const _value
				)
				{
					return
						fcppt::math::ceil_div(
							_value,
							fcppt::cast::size<
								sanguis::creator::grid::dim::value_type
							>(
								sanguis::client::draw2d::scene::world::batch_size::value
							)
						);
				}
			),
			[
				&_random_generator,
				_debug,
				&_grid,
				&_background_grid,
				&_tiles,
				&_sprite_buffers,
				batch_dim_pos,
				&tiles_log
			](
				sanguis::creator::pos const _pos
			)
			{
				sanguis::creator::min const min(
					_pos
					*
					batch_dim_pos
				);

				sanguis::creator::sup const sup(
					min.get()
					+
					batch_dim_pos
					+
					// TODO: Why?
					fcppt::math::vector::fill<
						sanguis::creator::pos
					>(
						1u
					)
				);

				sanguis::client::draw2d::scene::world::sprite::container sprites(
					fcppt::algorithm::map_optional<
						sanguis::client::draw2d::scene::world::sprite::container
					>(
						sanguis::tiles::draw(
							tiles_log,
							_grid,
							_background_grid,
							_tiles.collection(),
							min,
							sup
						),
						[
							&_random_generator,
							_debug,
							&_tiles
						](
							sanguis::tiles::cell const &_cell
						)
						{
							return
								sanguis::client::draw2d::scene::world::make_sprite(
									_random_generator,
									_debug,
									_tiles,
									_cell
								);
						}
					)
				);

				return
					sanguis::client::draw2d::scene::world::batch(
						sge::sprite::geometry::sort_and_update(
							sge::sprite::geometry::make_random_access_range(
								sprites
							),
							sanguis::client::draw2d::scene::world::sprite::compare(),
							_sprite_buffers
						)
					);
			}
		);
}
