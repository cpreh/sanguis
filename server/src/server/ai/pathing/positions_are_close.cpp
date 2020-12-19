#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/server/ai/pathing/positions_are_close.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/math/diff.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


bool
sanguis::server::ai::pathing::positions_are_close(
	sanguis::creator::pos const &_pos1,
	sanguis::creator::pos const &_pos2
)
{
	auto const spos1(
		fcppt::math::vector::structure_cast<
			sanguis::creator::signed_pos,
			fcppt::cast::to_signed_fun
		>(
			_pos1
		)
	);

	auto const spos2(
		fcppt::math::vector::structure_cast<
			sanguis::creator::signed_pos,
			fcppt::cast::to_signed_fun
		>(
			_pos2
		)
	);

	auto const close(
		[](
			sanguis::creator::difference_type const _d1,
			sanguis::creator::difference_type const _d2
		)
		{
			return
				fcppt::math::diff(
					_d1,
					_d2
				)
				<=
				fcppt::literal<
					sanguis::creator::difference_type
				>(
					1
				);
		}
	);

	return
		close(
			spos1.x(),
			spos2.x()
		)
		&&
		close(
			spos1.y(),
			spos2.y()
		);
}
