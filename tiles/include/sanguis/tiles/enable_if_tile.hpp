#ifndef SANGUIS_TILES_ENABLE_IF_TILE_HPP_INCLUDED
#define SANGUIS_TILES_ENABLE_IF_TILE_HPP_INCLUDED

#include <sanguis/tiles/is_tile.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{

template<
	typename Tile,
	typename Result
>
using
enable_if_tile
=
typename
boost::enable_if<
	sanguis::tiles::is_tile<
		Tile
	>,
	Result
>::type;

}
}

#endif
