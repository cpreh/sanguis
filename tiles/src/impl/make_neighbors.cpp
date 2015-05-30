#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/tiles/enable_if_tile.hpp>
#include <sanguis/tiles/impl/instantiate_tile.hpp>
#include <sanguis/tiles/impl/make_neighbors.hpp>
#include <sanguis/tiles/impl/neighbors.hpp>
#include <sanguis/tiles/impl/replace_non_connecting.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/grid/at_optional.hpp>


template<
	typename Tile
>
sanguis::tiles::enable_if_tile<
	Tile,
	sanguis::tiles::impl::neighbors<
		Tile
	>
>
sanguis::tiles::impl::make_neighbors(
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::creator::pos const _pos
)
{
	auto const get_tile(
		[
			&_grid
		](
			sanguis::creator::pos const _npos
		)
		-> Tile
		{
			return
				sanguis::tiles::impl::replace_non_connecting(
					FCPPT_ASSERT_OPTIONAL_ERROR(
						fcppt::container::grid::at_optional(
							_grid,
							_npos
						)
					)
				);
		}
	);

	typedef
	sanguis::tiles::impl::neighbors<
		Tile
	>
	result_type;

	return
		result_type{
			typename
			result_type::internal{{
				get_tile(
					sanguis::creator::pos{
						_pos.x() - 1,
						_pos.y() - 1
					}
				),
				get_tile(
					sanguis::creator::pos{
						_pos.x(),
						_pos.y() - 1
					}
				),
				get_tile(
					sanguis::creator::pos{
						_pos.x() - 1,
						_pos.y()
					}
				),
				get_tile(
					sanguis::creator::pos{
						_pos.x(),
						_pos.y()
					}
				)
			}}
		};
}

#define SANGUIS_TILES_INSTANTIATE_MAKE_NEIGHBORS(\
	tile_type\
)\
template \
sanguis::tiles::enable_if_tile<\
	tile_type,\
	sanguis::tiles::impl::neighbors<\
		tile_type \
	> \
> \
sanguis::tiles::impl::make_neighbors(\
	sanguis::creator::tile_grid< \
		tile_type \
	> const &, \
	sanguis::creator::pos \
)

SANGUIS_TILES_IMPL_INSTANTIATE_TILE(
	SANGUIS_TILES_INSTANTIATE_MAKE_NEIGHBORS
);
