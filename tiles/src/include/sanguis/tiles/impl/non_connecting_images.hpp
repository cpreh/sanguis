#ifndef SANGUIS_TILES_IMPL_NON_CONNECTING_IMAGES_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_NON_CONNECTING_IMAGES_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/tiles/collection_fwd.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/impl/error_message_function.hpp>
#include <sanguis/tiles/impl/filter_non_connecting.hpp>
#include <sanguis/tiles/impl/images_base.hpp>
#include <sanguis/tiles/impl/optional_content_path.hpp>
#include <sanguis/tiles/impl/to_string.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

template<
	typename Tile
>
sanguis::tiles::impl::optional_content_path
non_connecting_images(
	sanguis::tiles::collection &_collection,
	sanguis::tiles::error const _error_code,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::creator::pos const _pos
)
{
	Tile const tile{
		_grid[
			_pos
		]
	};

	return
		sanguis::tiles::impl::filter_non_connecting(
			tile
		)
		?
			sanguis::tiles::impl::optional_content_path{}
		:
			sanguis::tiles::impl::images_base(
				_collection,
				_error_code,
				sanguis::tiles::pair<
					Tile
				>(
					tile,
					tile
				),
				sanguis::tiles::orientation::null(),
				sanguis::tiles::impl::error_message_function{
					[
						tile
					]
					{
						return
							sanguis::tiles::impl::to_string(
								tile
							);
					}
				}
			)
		;
}

}
}
}

#endif
