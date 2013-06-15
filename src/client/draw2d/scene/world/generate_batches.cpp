#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/batch_size.hpp>
#include <sanguis/client/draw2d/scene/world/generate_batches.hpp>
#include <sanguis/client/draw2d/scene/world/tile_size.hpp>
#include <sanguis/client/draw2d/scene/world/to_tile_texture.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/buffers.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/object.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/parameters.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/load/tiles/context_fwd.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/geometry/sort_and_update.hpp>
#include <fcppt/container/grid/clamp_pos.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/math/map.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::batch_grid
sanguis::client::draw2d::scene::world::generate_batches(
	sanguis::creator::grid const &_grid,
	sanguis::load::tiles::context &_tiles,
	sanguis::client::draw2d::scene::world::sprite::buffers &_sprite_buffers
)
{
	sanguis::client::draw2d::scene::world::batch_grid ret(
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::scene::world::batch_grid::dim
		>(
			fcppt::math::map<
				sanguis::creator::size
			>(
				_grid.size(),
				[](
					sanguis::creator::size::value_type const _value
				)
				{
					return
						fcppt::math::ceil_div(
							_value,
							static_cast<
								sanguis::creator::size::value_type
							>(
								sanguis::client::draw2d::scene::world::batch_size::value
							)
						);
				}
			)
		)
	);

	typedef
	std::vector<
		sanguis::client::draw2d::scene::world::sprite::object
	>
	sprite_vector;

	sprite_vector sprites;

	sanguis::creator::size const batch_dim(
		fcppt::math::dim::fill<
			sanguis::creator::pos::dim_wrapper::value
		>(
			sanguis::client::draw2d::scene::world::batch_size::value
		)
	);

	sprites.reserve(
		batch_dim.content()
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
		sanguis::client::draw2d::scene::world::sprite::object::dim const tile_dim(
			fcppt::math::dim::fill<
				sanguis::client::draw2d::scene::world::sprite::object::dim::dim_wrapper::value
			>(
				sanguis::client::draw2d::scene::world::tile_size::value
			)
		);

		sanguis::creator::pos const
			lower_bound(
				fcppt::container::grid::clamp_pos(
					result_element.pos()
					*
					batch_dim_pos,
					_grid.size()
				)
			),
			upper_bound(
				fcppt::container::grid::clamp_pos(
					lower_bound
					+
					batch_dim_pos,
					_grid.size()
				)
			);

		for(
			auto const &source_element
			:
			fcppt::container::grid::make_pos_crange_start_end(
				_grid,
				lower_bound,
				upper_bound
			)
		)
		{
			if(
				source_element.value()
				==
				sanguis::creator::tile::nothing
			)
				continue;

			sprites.push_back(
				sanguis::client::draw2d::scene::world::sprite::object(
					sanguis::client::draw2d::scene::world::sprite::parameters()
					.pos(
						fcppt::math::vector::structure_cast<
							sanguis::client::draw2d::scene::world::sprite::object::vector
						>(
							source_element.pos()
						)
						*
						tile_dim
					)
					.size(
						tile_dim
					)
					.texture(
						sanguis::client::draw2d::scene::world::to_tile_texture(
							_tiles,
							_grid,
							source_element.pos()
						)
					)
				)
			);
		}

		result_element.value() =
			sanguis::client::draw2d::scene::world::batch(
				sge::sprite::geometry::sort_and_update(
					sge::sprite::geometry::make_random_access_range(
						sprites.begin(),
						sprites.end()
					),
					sge::sprite::compare::default_(),
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
