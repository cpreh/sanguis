#ifndef SANGUIS_TILES_IMPL_NEIGHBORS_TO_STRING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_NEIGHBORS_TO_STRING_HPP_INCLUDED

#include <sanguis/tiles/enable_if_tile.hpp>
#include <sanguis/tiles/impl/neighbors_fwd.hpp>
#include <fcppt/string.hpp>


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
	fcppt::string
>
neighbors_to_string(
	sanguis::tiles::impl::neighbors<
		Tile
	> const &
);

}
}
}

#endif
