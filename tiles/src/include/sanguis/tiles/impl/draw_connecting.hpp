#ifndef SANGUIS_TILES_IMPL_DRAW_CONNECTING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_DRAW_CONNECTING_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/collection_fwd.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/lower_bound.hpp>
#include <sanguis/tiles/pos.hpp>
#include <sanguis/tiles/unit.hpp>
#include <sanguis/tiles/upper_bound.hpp>
#include <sanguis/tiles/impl/connecting_images.hpp>
#include <sanguis/tiles/impl/draw_base.hpp>
#include <sanguis/tiles/impl/optional_content.hpp>
#include <sanguis/tiles/impl/shift.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/vector/fill.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

template<
	typename Tile
>
sanguis::tiles::cell_container
draw_connecting(
	sanguis::tiles::collection &_collection,
	sanguis::tiles::error const _error_code,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::tiles::lower_bound const _lower_bound,
	sanguis::tiles::upper_bound const _upper_bound
)
{
	return
		sanguis::tiles::impl::draw_base(
			_grid,
			_lower_bound,
			_upper_bound,
			sanguis::tiles::impl::shift(
				fcppt::math::vector::fill<
					sanguis::tiles::pos
				>(
					fcppt::cast::size<
						sanguis::tiles::unit
					>(
						fcppt::cast::to_signed(
							sanguis::creator::tile_size::value
						)
					)
					/
					fcppt::literal<
						sanguis::tiles::unit
					>(
						2
					)
				)
			),
			[
				&_collection,
				_error_code,
				&_grid
			](
				sanguis::creator::pos const _pos
			)
			-> sanguis::tiles::impl::optional_content
			{
				return
					sanguis::tiles::impl::connecting_images(
						_collection,
						_error_code,
						_grid,
						_pos
					);
			}
		);
}

}
}
}

#endif
