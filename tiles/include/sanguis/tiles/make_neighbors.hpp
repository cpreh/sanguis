#ifndef SANGUIS_TILES_MAKE_NEIGHBORS_HPP_INCLUDED
#define SANGUIS_TILES_MAKE_NEIGHBORS_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/tile_grid_fwd.hpp>
#include <sanguis/tiles/enable_if_tile.hpp>
#include <sanguis/tiles/neighbors.hpp>
#include <sanguis/tiles/symbol.hpp>


namespace sanguis
{
namespace tiles
{

template<
	typename Tile
>
SANGUIS_TILES_SYMBOL
sanguis::tiles::enable_if_tile<
	Tile,
	sanguis::tiles::neighbors<
		Tile
	>
>
make_neighbors(
	sanguis::creator::tile_grid<
		Tile
	> const &,
	sanguis::creator::pos
);

}
}

#endif
