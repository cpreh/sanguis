#include <sanguis/tiles/direction.hpp>
#include <sanguis/tiles/enable_if_tile.hpp>
#include <sanguis/tiles/make_orientation.hpp>
#include <sanguis/tiles/neighbors.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/impl/instantiate_tile.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/assert/error.hpp>


template<
	typename Tile
>
sanguis::tiles::enable_if_tile<
	Tile,
	sanguis::tiles::orientation
> const
sanguis::tiles::make_orientation(
	sanguis::tiles::pair<
		Tile
	> const &_pair,
	sanguis::tiles::neighbors<
		Tile
	> const &_neighbors
)
{
	sanguis::tiles::orientation orientation{
		sanguis::tiles::orientation::null()
	};

	// TODO: Check if the tile is _pair.second?
	for(
		sanguis::tiles::direction const value
		:
		fcppt::make_enum_range<
			sanguis::tiles::direction
		>()
	)
	{
		Tile const tile(
			_neighbors[
				value
			]
		);

		FCPPT_ASSERT_ERROR(
			tile
			==
			_pair.first()
			||
			tile
			==
			_pair.second()
		);

		orientation[
			value
		] =
			tile
			==
			_pair.first();
	}

	return
		orientation;
}

#define SANGUIS_TILES_INSTANTIATE_MAKE_ORIENTATION(\
	tile_type\
)\
template \
sanguis::tiles::enable_if_tile< \
	tile_type, \
	sanguis::tiles::orientation \
> const \
sanguis::tiles::make_orientation(\
	sanguis::tiles::pair<\
		tile_type\
	> const &,\
	sanguis::tiles::neighbors<\
		tile_type\
	> const & \
)

SANGUIS_TILES_IMPL_INSTANTIATE_TILE(
	SANGUIS_TILES_INSTANTIATE_MAKE_ORIENTATION
);
