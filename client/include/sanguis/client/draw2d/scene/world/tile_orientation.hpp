#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_ORIENTATION_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/tile_neighbors.hpp>
#include <sanguis/client/load/tiles/direction.hpp>
#include <sanguis/client/load/tiles/orientation.hpp>
#include <sanguis/client/load/tiles/pair.hpp>
#include <fcppt/make_enum_range.hpp>


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
sanguis::client::load::tiles::orientation const
tile_orientation(
	sanguis::client::load::tiles::pair<
		Tile
	> const &_pair,
	sanguis::client::draw2d::scene::world::tile_neighbors<
		Tile
	> const _neighbors
)
{
	sanguis::client::load::tiles::orientation orientation{
		sanguis::client::load::tiles::orientation::null()
	};

	// TODO: Check if the tile is _pair.second?
	for(
		sanguis::client::load::tiles::direction const value
		:
		fcppt::make_enum_range<
			sanguis::client::load::tiles::direction
		>()
	)
		orientation[
			value
		] =
			_neighbors[
				value
			]
			==
			_pair.first;

	return
		orientation;
}

}
}
}
}
}

#endif
