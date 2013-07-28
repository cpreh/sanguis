#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/batch_size.hpp>
#include <sanguis/client/draw2d/scene/world/fill_batches.hpp>
#include <sanguis/client/draw2d/scene/world/generate_batches.hpp>
#include <sanguis/client/draw2d/scene/world/is_background.hpp>
#include <sanguis/client/draw2d/scene/world/lower_bound.hpp>
#include <sanguis/client/draw2d/scene/world/tile_size.hpp>
#include <sanguis/client/draw2d/scene/world/upper_bound.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/compare.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/dim.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/vector.hpp>
#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/load/tiles/context_fwd.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/geometry/sort_and_update.hpp>
#include <fcppt/container/grid/clamp_pos.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/math/map.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::batch_grid
sanguis::client::draw2d::scene::world::generate_batches(
	sanguis::creator::grid const &_grid,
	sanguis::creator::background_grid const &_background_grid,
	sanguis::load::tiles::context &_tiles,
	sanguis::client::draw2d::scene::world::sprite::buffers &_sprite_buffers
)
{
	sanguis::client::draw2d::scene::world::batch_grid ret(
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::scene::world::batch_grid::dim
		>(
			fcppt::math::map<
				sanguis::creator::grid::dim
			>(
				_grid.size(),
				[](
					sanguis::creator::grid::dim::value_type const _value
				)
				{
					return
						fcppt::math::ceil_div(
							_value,
							static_cast<
								sanguis::creator::grid::dim::value_type
							>(
								sanguis::client::draw2d::scene::world::batch_size::value
							)
						);
				}
			)
		)
	);

	sanguis::client::draw2d::scene::world::sprite::vector sprites;

	sanguis::creator::grid::dim const batch_dim(
		fcppt::math::dim::fill<
			sanguis::creator::pos::dim_wrapper::value
		>(
			sanguis::client::draw2d::scene::world::batch_size::value
		)
	);

	sprites.reserve(
		batch_dim.content()
		*
		2u
	);

	sanguis::creator::pos const batch_dim_pos(
		fcppt::math::dim::structure_cast<
			sanguis::creator::pos
		>(
			batch_dim
		)
	);

	for(
		auto const &result_element
		:
		fcppt::container::grid::make_pos_range(
			ret
		)
	)
	{
		sanguis::client::draw2d::scene::world::sprite::dim const tile_dim(
			fcppt::math::dim::fill<
				sanguis::client::draw2d::scene::world::sprite::dim::dim_wrapper::value
			>(
				sanguis::client::draw2d::scene::world::tile_size::value
			)
		);

		sanguis::client::draw2d::scene::world::lower_bound const lower_bound(
			fcppt::container::grid::clamp_pos(
				result_element.pos()
				*
				batch_dim_pos,
				_grid.size()
			)
		);

		sanguis::client::draw2d::scene::world::upper_bound const upper_bound(
			fcppt::container::grid::clamp_pos(
				lower_bound.get()
				+
				batch_dim_pos,
				_grid.size()
			)
		);

		sprites =
			sanguis::client::draw2d::scene::world::fill_batches(
				std::move(
					sprites
				),
				_tiles,
				_grid,
				lower_bound,
				upper_bound,
				sanguis::creator::tile::nothing,
				tile_dim,
				sanguis::client::draw2d::scene::world::is_background(
					false
				)
			);

		sprites =
			sanguis::client::draw2d::scene::world::fill_batches(
				std::move(
					sprites
				),
				_tiles,
				_background_grid,
				lower_bound,
				upper_bound,
				sanguis::creator::background_tile::nothing,
				tile_dim,
				sanguis::client::draw2d::scene::world::is_background(
					true
				)
			);

		result_element.value() =
			sanguis::client::draw2d::scene::world::batch(
				sge::sprite::geometry::sort_and_update(
					sge::sprite::geometry::make_random_access_range(
						sprites.begin(),
						sprites.end()
					),
					sanguis::client::draw2d::scene::world::sprite::compare(),
					_sprite_buffers
				)
			);

		sprites.clear();
	}

	return
		std::move(
			ret
		);
}
