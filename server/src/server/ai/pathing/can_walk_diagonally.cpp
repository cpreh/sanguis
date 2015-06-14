#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/server/ai/pathing/can_walk_diagonally.hpp>
#include <sanguis/server/ai/pathing/positions_are_close.hpp>
#include <fcppt/const.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/algorithm/all_of.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <initializer_list>
#include <fcppt/config/external_end.hpp>


bool
sanguis::server::ai::pathing::can_walk_diagonally(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const _pos1,
	sanguis::creator::pos const _pos2
)
{
	if(
		_pos1
		==
		_pos2
	)
		return
			true;

	if(
		!sanguis::server::ai::pathing::positions_are_close(
			_pos1,
			_pos2
		)
	)
		return
			false;

	sanguis::creator::signed_pos const spos1(
		fcppt::math::vector::structure_cast<
			sanguis::creator::signed_pos,
			fcppt::cast::to_signed_fun
		>(
			_pos1
		)
	);

	sanguis::creator::signed_pos const spos2(
		fcppt::math::vector::structure_cast<
			sanguis::creator::signed_pos,
			fcppt::cast::to_signed_fun
		>(
			_pos2
		)
	);

	sanguis::creator::signed_pos const diff(
		spos1
		-
		spos2
	);

	return
		fcppt::algorithm::all_of(
			std::initializer_list<
				sanguis::creator::signed_pos
			>
			{
				spos1,
				spos2,
				sanguis::creator::signed_pos(
					spos2.x()
					+
					diff.x(),
					spos2.y()
				),
				sanguis::creator::signed_pos(
					spos2.x(),
					spos2.y()
					+
					diff.y()
				)
			},
			[
				&_grid
			](
				sanguis::creator::signed_pos const _spos
			)
			{
				return
					fcppt::maybe(
						fcppt::container::grid::at_optional(
							_grid,
							fcppt::math::vector::structure_cast<
								sanguis::creator::pos,
								fcppt::cast::to_unsigned_fun
							>(
								_spos
							)
						),
						fcppt::const_(
							true
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
