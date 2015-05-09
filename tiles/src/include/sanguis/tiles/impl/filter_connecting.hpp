#ifndef SANGUIS_TILES_IMPL_FILTER_CONNECTING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_FILTER_CONNECTING_HPP_INCLUDED

#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_connects.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

inline
sanguis::creator::tile
filter_connecting(
	sanguis::creator::tile const _tile
)
{
	return
		sanguis::creator::tile_connects(
			_tile
		)
		?
			_tile
		:
			sanguis::creator::tile::nothing
		;
}

inline
sanguis::creator::background_tile
filter_connecting(
	sanguis::creator::background_tile const _tile
)
{
	return
		_tile;
}

}
}
}

#endif
