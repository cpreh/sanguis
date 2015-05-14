#ifndef SANGUIS_TILES_IMPL_MAKE_NEIGHBORS_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_MAKE_NEIGHBORS_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/tile_grid_fwd.hpp>
#include <sanguis/tiles/enable_if_tile.hpp>
#include <sanguis/tiles/impl/neighbors.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

template<
	typename Tile
>
sanguis::tiles::enable_if_tile<
	Tile,
	sanguis::tiles::impl::neighbors<
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
}

#endif
