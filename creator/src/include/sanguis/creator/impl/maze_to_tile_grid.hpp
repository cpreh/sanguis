#ifndef SANGUIS_CREATOR_IMPL_MAZE_TO_TILE_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_MAZE_TO_TILE_GRID_HPP_INCLUDED

#include <sanguis/creator/impl/reachable_grid.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <sanguis/creator/impl/maze_to_tile_grid.hpp>
#include <fcppt/container/grid/make_pos_crange.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>

namespace sanguis
{
namespace creator
{
namespace impl
{

template<
	typename Tile
>
sanguis::creator::tile_grid<
	Tile
>
maze_to_tile_grid(
	sanguis::creator::impl::reachable_grid _maze,
	unsigned const _wall_thickness,
	unsigned const _spacing,
	Tile const _empty,
	Tile const _wall
)
{
	using grid_type = sanguis::creator::tile_grid<
		Tile
	>;

	using dim_type = sanguis::creator::impl::reachable_grid::dim;

	dim_type const real_size(
		(
			_maze.size()
			-
			dim_type(
				1u,
				1u)
		)
		/
		2u
	);

	dim_type const result_size(
		real_size
		*
		_spacing +
		(
			real_size
			+
			dim_type(
				1u,
				1u)
		)
		* _wall_thickness
	);

	auto const coordinate_transform =
		[
			_wall_thickness,
			_spacing
		](dim_type::value_type a)
		{
			return
				(a / 2) * _spacing
				+
				((a + 1) / 2) * _wall_thickness;
		};

	auto const wall_or_space =
		[
			_wall_thickness,
			_spacing
		](dim_type::value_type a)
		{
			return
			a % 2 == 0
			?
			_wall_thickness
			:
			_spacing;
		};

	grid_type result{
		dim_type(
			result_size)};

	for(
		auto cell :
		fcppt::container::grid::make_pos_crange(
			_maze)
	)
	{
		typename grid_type::pos const start(
			coordinate_transform(cell.pos().x()),
			coordinate_transform(cell.pos().y()));

		dim_type const cell_size(
			wall_or_space(cell.pos().x()),
			wall_or_space(cell.pos().y()));

		for(
			dim_type::value_type y = 0u;
			y < cell_size.h();
			++y
		)
			for(
				dim_type::value_type x = 0u;
				x < cell_size.w();
				++x
			)
				result
				[
					start
					+
					dim_type(
						x,
						y
					)
				] =
				(
					cell.value() ==
					sanguis::creator::impl::reachable(true)
					?
					_empty
					:
					_wall
				);
	}

	return result;
}

}
}
}

#endif
