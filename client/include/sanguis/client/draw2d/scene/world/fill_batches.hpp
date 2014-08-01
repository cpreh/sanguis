#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILL_BATCHES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILL_BATCHES_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/is_background.hpp>
#include <sanguis/client/draw2d/scene/world/lower_bound.hpp>
#include <sanguis/client/draw2d/scene/world/to_tile_texture.hpp>
#include <sanguis/client/draw2d/scene/world/upper_bound.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/dim.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/is_background_role.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/parameters.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/object.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/vector.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
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
sanguis::client::draw2d::scene::world::sprite::vector
fill_batches(
	sanguis::client::draw2d::scene::world::sprite::vector &&_sprites,
	sanguis::client::load::tiles::context &_tiles,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::client::draw2d::scene::world::lower_bound const &_lower_bound,
	sanguis::client::draw2d::scene::world::upper_bound const &_upper_bound,
	sanguis::client::draw2d::scene::world::sprite::dim const &_tile_dim,
	sanguis::client::draw2d::scene::world::is_background const _is_background
)
{
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
		// TODO: optional_unique_ptr
		sge::texture::const_part_shared_ptr const texture(
			sanguis::client::draw2d::scene::world::to_tile_texture(
				_tiles,
				_grid,
				source_element.pos()
			)
		);

		if(
			!texture
		)
			continue;

		_sprites.push_back(
			sanguis::client::draw2d::scene::world::sprite::object(
				sanguis::client::draw2d::scene::world::sprite::parameters()
				.pos(
					fcppt::math::vector::structure_cast<
						sanguis::client::draw2d::scene::world::sprite::object::vector
					>(
						source_element.pos()
					)
					*
					_tile_dim
					-
					_tile_dim
					/
					fcppt::literal<
						sanguis::client::draw2d::scene::world::sprite::dim::value_type
					>(
						2
					)
				)
				.size(
					_tile_dim
				)
				.texture(
					texture
				)
				.template set<
					sanguis::client::draw2d::scene::world::sprite::is_background_role
				>(
					_is_background.get()
				)
			)
		);
	}

	return
		std::move(
			_sprites
		);
}

}
}
}
}
}

#endif
