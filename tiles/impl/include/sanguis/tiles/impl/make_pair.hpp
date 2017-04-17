#ifndef SANGUIS_TILES_IMPL_MAKE_PAIR_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_MAKE_PAIR_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/tiles/impl/neighbors_fwd.hpp>
#include <sanguis/tiles/impl/optional_pair.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
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
}
}

#endif
