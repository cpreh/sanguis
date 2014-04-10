#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::creator::pos const
sanguis::server::world::center_to_grid_pos(
	sanguis::server::center const _center
)
{
	return
		fcppt::math::vector::structure_cast<
			sanguis::creator::pos
		>(
			_center.get()
		)
		/
		sanguis::creator::tile_size::value;
}
