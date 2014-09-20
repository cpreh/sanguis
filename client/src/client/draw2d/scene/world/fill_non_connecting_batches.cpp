#include <sanguis/client/draw2d/scene/world/fill_non_connecting_batches.hpp>
#include <sanguis/client/draw2d/scene/world/lower_bound.hpp>
#include <sanguis/client/draw2d/scene/world/tile_size.hpp>
#include <sanguis/client/draw2d/scene/world/to_non_connecting_tile_texture.hpp>
#include <sanguis/client/draw2d/scene/world/upper_bound.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/dim.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/is_background_role.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/object.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/parameters.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/vector.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::sprite::vector
sanguis::client::draw2d::scene::world::fill_non_connecting_batches(
	sanguis::client::draw2d::scene::world::sprite::vector &&_sprites,
	sanguis::client::load::tiles::context &_tiles,
	sanguis::creator::grid const &_grid,
	sanguis::client::draw2d::scene::world::lower_bound const &_lower_bound,
	sanguis::client::draw2d::scene::world::upper_bound const &_upper_bound
)
{
	// TODO: Put this in a function
	sanguis::client::draw2d::scene::world::sprite::dim const tile_dim(
		fcppt::math::dim::fill<
			sanguis::client::draw2d::scene::world::sprite::dim::dim_wrapper::value
		>(
			sanguis::client::draw2d::scene::world::tile_size::value
		)
	);

	// TODO: map_optional by moving _sprites
	for(
		auto const &source_element
		:
		fcppt::container::grid::make_pos_crange_start_end(
			_grid,
			_lower_bound.get(),
			_upper_bound.get()
		)
	)
	{
		sge::texture::const_optional_part_ref const texture(
			sanguis::client::draw2d::scene::world::to_non_connecting_tile_texture(
				_tiles,
				source_element.value()
			)
		);

		if(
			!texture
		)
			continue;

		_sprites.push_back(
			sanguis::client::draw2d::scene::world::sprite::object(
				sanguis::client::draw2d::scene::world::sprite::parameters()
				// TODO: Put this in a function
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
					sanguis::client::draw2d::scene::world::sprite::object::texture_type{
						texture
					}
				)
				.set<
					sanguis::client::draw2d::scene::world::sprite::is_background_role
				>(
					false
				)
			)
		);
	}

	return
		std::move(
			_sprites
		);

}
