#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_TILE_PAIR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_TILE_PAIR_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/tile_neighbors.hpp>
#include <sanguis/client/load/tiles/direction.hpp>
#include <sanguis/client/load/tiles/optional_pair.hpp>
#include <sanguis/client/load/tiles/pair.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/size.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

template<
	typename Tile
>
sanguis::client::load::tiles::optional_pair<
	Tile
>
make_tile_pair(
	sanguis::client::draw2d::scene::world::tile_neighbors<
		Tile
	> _tiles
)
{
	auto const range(
		boost::range::unique(
			boost::range::sort(
				_tiles
			)
		)
	);

	typedef
	sanguis::client::load::tiles::optional_pair<
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

}
}
}
}
}

#endif
