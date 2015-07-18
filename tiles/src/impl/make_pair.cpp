#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/impl/make_pair.hpp>
#include <sanguis/tiles/impl/neighbors.hpp>
#include <sanguis/tiles/impl/optional_pair.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/size.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Tile
>
sanguis::creator::enable_if_tile<
	Tile,
	sanguis::tiles::impl::optional_pair<
		Tile
	>
>
sanguis::tiles::impl::make_pair(
	sanguis::tiles::impl::neighbors<
		Tile
	> _neighbors
)
{
	auto const range(
		boost::range::unique(
			boost::range::sort(
				_neighbors
			)
		)
	);

	typedef
	sanguis::tiles::impl::optional_pair<
		Tile
	>
	result_type;

	typedef
	typename
	result_type::value_type
	pair_type;

	switch(
		boost::size(
			range
		)
	)
	{
	case 1:
		return
			result_type(
				pair_type(
					range[0],
					range[0]
				)
			);
	case 2:
		return
			result_type(
				pair_type(
					range[0],
					range[1]
				)
			);
	}

	return
		result_type();
}

#define SANGUIS_TILES_INSTANTIATE_MAKE_PAIR(\
	tile_type\
)\
template \
sanguis::creator::enable_if_tile<\
	tile_type,\
	sanguis::tiles::impl::optional_pair<\
		tile_type\
	> \
>\
sanguis::tiles::impl::make_pair(\
	sanguis::tiles::impl::neighbors<\
		tile_type\
	>\
)

SANGUIS_CREATOR_INSTANTIATE_TILE(
	SANGUIS_TILES_INSTANTIATE_MAKE_PAIR
);
