#ifndef SANGUIS_TILES_IMPL_MAKE_PAIR_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_MAKE_PAIR_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/impl/neighbors_fwd.hpp>
#include <sanguis/tiles/impl/optional_pair.hpp>


namespace sanguis::tiles::impl
{

template<
	typename Tile
>
sanguis::creator::enable_if_tile<
	Tile,
	sanguis::tiles::impl::optional_pair<
		Tile
	>
>
make_pair(
	sanguis::tiles::impl::neighbors<
		Tile
	>
);

}

#define SANGUIS_TILES_DECLARE_MAKE_PAIR(\
	tile_type\
)\
extern \
template \
sanguis::creator::enable_if_tile<\
	tile_type,\
	sanguis::tiles::impl::optional_pair<\
		tile_type\
	> \
>\
sanguis::tiles::impl::make_pair(\
	sanguis::tiles::impl::neighbors<\
		tile_type\
	>\
)

SANGUIS_CREATOR_INSTANTIATE_TILE(
	SANGUIS_TILES_DECLARE_MAKE_PAIR
);

#endif
