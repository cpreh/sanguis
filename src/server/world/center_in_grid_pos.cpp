#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/world/center_in_grid_pos.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


bool
sanguis::server::world::center_in_grid_pos(
	sanguis::server::center const _center,
	sanguis::creator::pos const _pos
)
{
	return
		fcppt::math::vector::structure_cast<
			sanguis::creator::pos
		>(
			_center.get()
			*
			fcppt::cast::int_to_float<
				sanguis::server::space_unit
			>(
				sanguis::pixels_per_meter()
			)
		)
		/
		sanguis::creator::tile_size::value
		==
		_pos;
}
