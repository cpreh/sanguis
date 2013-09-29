#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/pathing/positions_are_close.hpp>
#include <fcppt/math/vector/distance.hpp>


bool
sanguis::server::ai::pathing::positions_are_close(
	sanguis::creator::pos const _pos1,
	sanguis::creator::pos const _pos2
)
{
	return
		fcppt::math::vector::distance<
			float
		>(
			_pos1,
			_pos2
		)
		< 2.f;
}
