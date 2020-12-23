#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/pair.hpp>
#include <fcppt/tuple/get.hpp>


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
		fcppt::tuple::get<0U>(
			impl_
		);
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
		fcppt::tuple::get<1U>(
			impl_
		);
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
