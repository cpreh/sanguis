#ifndef SANGUIS_TILES_IMPL_NAME_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_NAME_HPP_INCLUDED

#include <sanguis/tiles/enable_if_tile.hpp>
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
name(
	Tile
);

}
}
}

#endif
