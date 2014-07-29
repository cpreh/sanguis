#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_TILE_NEIGHBORS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_TILE_NEIGHBORS_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/tile_neighbors.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/grid/in_range.hpp>


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
sanguis::client::draw2d::scene::world::tile_neighbors<
	Tile
>
make_tile_neighbors(
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
			// TODO: Remove this once everything works
			FCPPT_ASSERT_PRE(
				fcppt::container::grid::in_range(
					_grid,
					_npos
				)
			);

			return
				_grid[
					_npos
				];
		}
	);

	typedef
	sanguis::client::draw2d::scene::world::tile_neighbors<
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

}
}
}
}
}

#endif
