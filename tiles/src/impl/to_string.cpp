#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/tiles/enable_if_tile.hpp>
#include <sanguis/tiles/impl/background_tile_name.hpp>
#include <sanguis/tiles/impl/instantiate_tile.hpp>
#include <sanguis/tiles/impl/to_string.hpp>
#include <sanguis/tiles/impl/tile_name.hpp>
#include <fcppt/string.hpp>


namespace
{

fcppt::string
name_any(
	sanguis::creator::tile const _tile
)
{
	return
		sanguis::tiles::impl::tile_name(
			_tile
		);
}

fcppt::string
name_any(
	sanguis::creator::background_tile const _tile
)
{
	return
		sanguis::tiles::impl::background_tile_name(
			_tile
		);
}

}

template<
	typename Tile
>
sanguis::tiles::enable_if_tile<
	Tile,
	fcppt::string
>
sanguis::tiles::impl::to_string(
	Tile const _tile
)
{
	return
		name_any(
			_tile
		);
}

#define SANGUIS_TILES_INSTANTIATE_TO_STRING(\
	tile_type\
)\
template \
sanguis::tiles::enable_if_tile< \
	tile_type, \
	fcppt::string \
> \
sanguis::tiles::impl::to_string(\
	tile_type \
)

SANGUIS_TILES_IMPL_INSTANTIATE_TILE(
	SANGUIS_TILES_INSTANTIATE_TO_STRING
);
