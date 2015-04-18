#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILL_BATCHES_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILL_BATCHES_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/is_background.hpp>
#include <sanguis/client/draw2d/scene/world/lower_bound.hpp>
#include <sanguis/client/draw2d/scene/world/tile_size.hpp>
#include <sanguis/client/draw2d/scene/world/upper_bound.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/container.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/dim.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/is_background_role.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/object.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/vector.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_signed.hpp>
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
	typename Tile,
	typename Transform,
	typename GetTexture
>
sanguis::client::draw2d::scene::world::sprite::container
fill_batches_base(
	sanguis::client::draw2d::scene::world::sprite::container &&_sprites,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::client::draw2d::scene::world::lower_bound const &_lower_bound,
	sanguis::client::draw2d::scene::world::upper_bound const &_upper_bound,
	sanguis::client::draw2d::scene::world::is_background const _is_background,
	Transform const &_transform,
	GetTexture const &_get_texture
)
{
	sanguis::client::draw2d::scene::world::sprite::dim const tile_dim(
		fcppt::math::dim::fill<
			sanguis::client::draw2d::scene::world::sprite::dim
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
		fcppt::maybe_void(
			_get_texture(
				source_element.pos()
			),
			[
				&_sprites,
				&_transform,
				_is_background,
				&source_element,
				tile_dim
			](
				sge::texture::part const &_texture
			)
			{
				_sprites.push_back(
					sanguis::client::draw2d::scene::world::sprite::object(
						sge::sprite::roles::pos{} =
							_transform(
								fcppt::math::vector::structure_cast<
									sanguis::client::draw2d::scene::world::sprite::vector,
									fcppt::cast::size_fun
								>(
									fcppt::math::vector::to_signed(
										source_element.pos()
									)
								)
								*
								tile_dim
							),
						sge::sprite::roles::size{} =
							tile_dim,
						sge::sprite::roles::texture0{} =
							sanguis::client::draw2d::scene::world::sprite::object::texture_type{
								_texture
							},
						sanguis::client::draw2d::scene::world::sprite::is_background_role{} =
							_is_background.get()
					)
				);
			}
		);

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
