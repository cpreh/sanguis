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
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/result.hpp>
#include <sanguis/creator/size.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/geometry/sort_and_update.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/math/map.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::batch_grid
sanguis::client::draw2d::scene::world::generate_batches(
	sanguis::creator::top_parameters const &_parameters,
	sanguis::load::resource::textures const &_textures,
	sanguis::client::draw2d::scene::world::sprite::buffers &_sprite_buffers
)
{
	sanguis::creator::result const generated(
		sanguis::creator::generate(
			_parameters
		)
	);

	sanguis::creator::grid const &grid(
		generated.grid()
	);

	sanguis::client::draw2d::scene::world::batch_grid ret(
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::scene::world::batch_grid::dim
		>(
			fcppt::math::map<
				sanguis::creator::size
			>(
				grid.size(),
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

	sanguis::creator::pos const batch_dim(
		fcppt::math::dim::fill<
			sanguis::creator::pos::dim_wrapper::value
		>(
			sanguis::client::draw2d::scene::world::batch_size::value
		)
	);

	sprites.reserve(
		batch_dim.content()
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
				result_element.pos()
				*
				batch_dim
			),
			upper_bound(
				lower_bound
				+
				batch_dim
			);

		for(
			auto const &source_element
			:
			fcppt::container::grid::make_pos_crange_start_end(
				grid,
				lower_bound,
				upper_bound
			)
		)
			sprites.push_back(
				sanguis::client::draw2d::scene::world::sprite::object(
					sanguis::client::draw2d::scene::world::sprite::parameters()
					.pos(
						fcppt::math::dim::structure_cast<
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
							_textures,
							source_element.value()
						)
					)
				)
			);

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
