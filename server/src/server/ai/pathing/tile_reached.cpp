#include <sanguis/creator/tile_size.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/pathing/tile_reached.hpp>
#include <sanguis/server/collision/distance_pos_pos.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <fcppt/cast/int_to_float.hpp>


bool
sanguis::server::ai::pathing::tile_reached(
	sanguis::server::entities::with_ai const &_me,
	sanguis::creator::pos const &_pos
)
{
	return
		sanguis::server::collision::distance_pos_pos(
			sanguis::server::world::grid_pos_to_center(
				_pos
			).get(),
			_me.center().get()
		)
		<
		fcppt::cast::int_to_float<
			sanguis::server::space_unit
		>(
			sanguis::creator::tile_size::value
			/
			2U
		)
		-
		_me.radius().get();
}
