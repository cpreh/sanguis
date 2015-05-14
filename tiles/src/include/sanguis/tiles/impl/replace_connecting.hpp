#ifndef SANGUIS_TILES_IMPL_REPLACE_CONNECTING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_REPLACE_CONNECTING_HPP_INCLUDED

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
replace_connecting(
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
replace_connecting(
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
