#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/server/ai/pathing/can_walk_diagonally.hpp>
#include <sanguis/server/ai/pathing/positions_are_close.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


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
			sanguis::creator::signed_pos
		>(
			_pos1
		)
	);

	sanguis::creator::signed_pos const spos2(
		fcppt::math::vector::structure_cast<
			sanguis::creator::signed_pos
		>(
			_pos2
		)
	);

	sanguis::creator::signed_pos const diff(
		spos1
		-
		spos2
	);

	for(
		sanguis::creator::signed_pos const spos
		:
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
		}
	)
	{
		sanguis::creator::pos const pos(
			fcppt::math::vector::structure_cast<
				sanguis::creator::pos
			>(
				spos
			)
		);

		if(
			fcppt::container::grid::in_range(
				_grid,
				pos
			)
			&&
			sanguis::creator::tile_is_solid(
				_grid[
					pos
				]
			)
		)
			return
				false;
	}

	return
		true;
}
