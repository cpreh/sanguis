#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/impl/neighbors.hpp>
#include <sanguis/tiles/impl/neighbors_to_string.hpp>
#include <sanguis/tiles/impl/to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


template<
	typename Tile
>
sanguis::creator::enable_if_tile<
	Tile,
	fcppt::string
>
sanguis::tiles::impl::neighbors_to_string(
	sanguis::tiles::impl::neighbors<
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
						sanguis::tiles::impl::to_string(
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

#define SANGUIS_TILES_INSTANTIATE_NEIGHBORS_TO_STRING(\
	tile_type\
)\
template \
sanguis::creator::enable_if_tile< \
	tile_type, \
	fcppt::string \
> \
sanguis::tiles::impl::neighbors_to_string(\
	sanguis::tiles::impl::neighbors<\
		tile_type\
	> const &\
)

SANGUIS_CREATOR_INSTANTIATE_TILE(
	SANGUIS_TILES_INSTANTIATE_NEIGHBORS_TO_STRING
);
