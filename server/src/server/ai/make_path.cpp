#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/make_path.hpp>


bool
sanguis::server::ai::make_path(
	sanguis::server::ai::context &_context,
	sanguis::creator::pos const _pos
)
{
	return
		!sanguis::creator::tile_is_solid(
			_context.grid()[
				_pos
			]
		)
		&&
		_context.path_find(
			_pos
		);
}
