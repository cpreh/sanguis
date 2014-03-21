#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_visible.hpp>
#include <sanguis/server/ai/pathing/is_visible.hpp>


bool
sanguis::server::ai::pathing::is_visible(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const _pos1,
	sanguis::creator::pos const _pos2
)
{
	return
		sanguis::creator::tile_is_visible(
			_grid,
			_pos1,
			_pos2
		);
}
