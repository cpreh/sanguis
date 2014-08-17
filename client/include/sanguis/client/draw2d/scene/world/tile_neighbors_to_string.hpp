#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_NEIGHBORS_TO_STRING_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_NEIGHBORS_TO_STRING_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/tile_neighbors.hpp>
#include <sanguis/client/load/tiles/to_name_any.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
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
fcppt::string
tile_neighbors_to_string(
	sanguis::client::draw2d::scene::world::tile_neighbors<
		Tile
	> const &_tiles
)
{
	return
		fcppt::string{
			'('
		}
		+
		fcppt::algorithm::join_strings(
			fcppt::algorithm::map<
				std::vector<
					fcppt::string
				>
			>(
				_tiles,
				[](
					Tile const _tile
				)
				{
					return
						sanguis::client::load::tiles::to_name_any(
							_tile
						);
				}
			),
			FCPPT_TEXT(",")
		)
		+
		fcppt::string{
			')'
		};
}

}
}
}
}
}

#endif
