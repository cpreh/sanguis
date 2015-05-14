#include <sanguis/tiles/enable_if_tile.hpp>
#include <sanguis/tiles/collection.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/set.hpp>
#include <sanguis/tiles/impl/instantiate_tile.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::tiles::collection::collection(
	sge::image2d::system &_image_system
)
:
	image_system_(
		_image_system
	),
	tiles_()
{
}

sanguis::tiles::collection::~collection()
{
}

template<
	typename Tile
>
sanguis::tiles::enable_if_tile<
	Tile,
	sanguis::tiles::set<
		Tile
	> const &
>
sanguis::tiles::collection::set(
	sanguis::tiles::pair<
		Tile
	> const _pair
)
{
	return
		fcppt::container::get_or_insert(
			boost::fusion::at_key<
				tile_map<
					Tile
				>
			>(
				tiles_
			),
			_pair,
			[
				this
			](
				sanguis::tiles::pair<
					Tile
				> const _key
			)
			{
				return
					sanguis::tiles::set<
						Tile
					>(
						image_system_,
						_key
					);
			}
		);
}

#define SANGUIS_TILES_INSTANTIATE_COLLECTION_SET(\
	tile_type\
)\
template \
sanguis::tiles::enable_if_tile<\
	tile_type,\
	sanguis::tiles::set<\
		tile_type\
	> const &\
> \
sanguis::tiles::collection::set(\
	sanguis::tiles::pair<\
		tile_type \
	>\
)

SANGUIS_TILES_IMPL_INSTANTIATE_TILE(
	SANGUIS_TILES_INSTANTIATE_COLLECTION_SET
);
