#ifndef SANGUIS_TILES_IMPL_IS_BACKGROUND_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_IS_BACKGROUND_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/is_background.hpp>


namespace sanguis::tiles::impl
{

template<
	typename Tile
>
sanguis::creator::enable_if_tile<
	Tile,
	sanguis::tiles::is_background
>
is_background();

}

#define SANGUIS_TILES_DECLARE_IS_BACKGROUND(\
	tile_type\
)\
extern \
template \
sanguis::creator::enable_if_tile< \
	tile_type,\
	sanguis::tiles::is_background\
> \
sanguis::tiles::impl::is_background<\
	tile_type\
>()

SANGUIS_CREATOR_INSTANTIATE_TILE(
	SANGUIS_TILES_DECLARE_IS_BACKGROUND
);

#endif
