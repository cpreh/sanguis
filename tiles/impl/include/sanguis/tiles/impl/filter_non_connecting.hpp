#ifndef SANGUIS_TILES_IMPL_FILTER_NON_CONNECTING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_FILTER_NON_CONNECTING_HPP_INCLUDED

#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_connects.hpp>


namespace sanguis::tiles::impl
{

inline
bool
filter_non_connecting(
	sanguis::creator::tile const _tile
)
{
	return
		_tile
		==
		sanguis::creator::tile::nothing
		||
		sanguis::creator::tile_connects(
			_tile
		);
}

inline
bool
filter_non_connecting(
	sanguis::creator::background_tile
)
{
	return
		false;
}

}

#endif
