#ifndef SANGUIS_TILES_MAKE_ORIENTATION_HPP_INCLUDED
#define SANGUIS_TILES_MAKE_ORIENTATION_HPP_INCLUDED

#include <sanguis/tiles/enable_if_tile.hpp>
#include <sanguis/tiles/neighbors_fwd.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/pair_fwd.hpp>
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
	sanguis::tiles::orientation
> const
make_orientation(
	sanguis::tiles::pair<
		Tile
	> const &,
	sanguis::tiles::neighbors<
		Tile
	> const &
);

}
}

#endif
