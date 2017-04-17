#ifndef SANGUIS_TILES_IMPL_IS_BACKGROUND_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_IS_BACKGROUND_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/tiles/is_background.hpp>


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
	sanguis::tiles::is_background
>
is_background();

}
}
}

#endif
