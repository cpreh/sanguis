#include <sanguis/creator/center_to_grid_pos.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>


sanguis::creator::pos
sanguis::server::world::center_to_grid_pos(
	sanguis::server::center const _center
)
{
	return
		sanguis::creator::center_to_grid_pos(
			_center.get()
		);
}
