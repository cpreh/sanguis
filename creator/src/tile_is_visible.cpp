#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_is_visible.hpp>
#include <fcppt/const.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/math/bresenham.hpp>
#include <fcppt/math/bresenham_thick.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/maybe.hpp>


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
				return
					fcppt::optional::maybe(
						fcppt::optional::copy_value(
							fcppt::container::grid::at_optional(
								_grid,
								fcppt::math::vector::structure_cast<
									sanguis::creator::pos,
									fcppt::cast::to_unsigned_fun
								>(
									_elem
								)
							)
						),
						fcppt::const_(
							false
						),
						[](
							sanguis::creator::tile const _tile
						)
						{
							return
								!sanguis::creator::tile_is_solid(
									_tile
								);
						}
					);
			}
		);
}
