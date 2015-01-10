#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_is_visible.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/math/bresenham.hpp>
#include <fcppt/math/bresenham_thick.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


bool
sanguis::creator::tile_is_visible(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const &_pos1,
	sanguis::creator::pos const &_pos2
)
{
	return
		fcppt::math::bresenham_thick(
			fcppt::math::vector::structure_cast<
				sanguis::creator::signed_pos,
				fcppt::cast::to_signed_fun
			>(
				_pos1
			),
			fcppt::math::vector::structure_cast<
				sanguis::creator::signed_pos,
				fcppt::cast::to_signed_fun
			>(
				_pos2
			),
			[
				&_grid
			](
				sanguis::creator::signed_pos const _elem
			)
			{
				sanguis::creator::pos const pos(
					fcppt::math::vector::structure_cast<
						sanguis::creator::pos,
						fcppt::cast::to_unsigned_fun
					>(
						_elem
					)
				);

				return
					fcppt::container::grid::in_range(
						_grid,
						pos
					)
					&&
					!sanguis::creator::tile_is_solid(
						_grid[
							pos
						]
					);
			}
		);
}
