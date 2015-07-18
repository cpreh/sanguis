#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/pair.hpp>


template<
	typename Tile
>
sanguis::tiles::pair<
	Tile
>::pair(
	Tile const _tile1,
	Tile const _tile2
)
:
	impl_(
		_tile1
		<
		_tile2
		?
			impl_type(
				_tile1,
				_tile2
			)
		:
			impl_type(
				_tile2,
				_tile1
			)
	)
{
}

template<
	typename Tile
>
Tile
sanguis::tiles::pair<
	Tile
>::first() const
{
	return
		impl_.first;
}

template<
	typename Tile
>
Tile
sanguis::tiles::pair<
	Tile
>::second() const
{
	return
		impl_.second;
}

#define SANGUIS_TILES_INSTANTIATE_TILE(\
	tile_type\
)\
template \
class \
sanguis::tiles::pair<\
	tile_type \
>

SANGUIS_CREATOR_INSTANTIATE_TILE(
	SANGUIS_TILES_INSTANTIATE_TILE
);
