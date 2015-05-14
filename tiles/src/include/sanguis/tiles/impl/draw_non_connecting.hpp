#ifndef SANGUIS_TILES_IMPL_DRAW_NON_CONNECTING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_DRAW_NON_CONNECTING_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/collection_fwd.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/lower_bound.hpp>
#include <sanguis/tiles/pos.hpp>
#include <sanguis/tiles/upper_bound.hpp>
#include <sanguis/tiles/impl/draw_base.hpp>
#include <sanguis/tiles/impl/non_connecting_images.hpp>
#include <sanguis/tiles/impl/shift.hpp>


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
draw_non_connecting(
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
			sanguis::tiles::impl::shift{
				sanguis::tiles::pos::null()
			},
			[
				&_collection,
				&_grid,
				_error_code
			](
				sanguis::creator::pos const _pos
			)
			{
				return
					sanguis::tiles::impl::non_connecting_images(
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
