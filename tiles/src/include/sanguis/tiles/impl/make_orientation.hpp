#ifndef SANGUIS_TILES_IMPL_MAKE_ORIENTATION_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_MAKE_ORIENTATION_HPP_INCLUDED

#include <sanguis/tiles/enable_if_tile.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/pair_fwd.hpp>
#include <sanguis/tiles/impl/neighbors_fwd.hpp>


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
	sanguis::tiles::orientation
> const
make_orientation(
	sanguis::tiles::pair<
		Tile
	> const &,
	sanguis::tiles::impl::neighbors<
		Tile
	> const &
);

}
}
}

#endif
