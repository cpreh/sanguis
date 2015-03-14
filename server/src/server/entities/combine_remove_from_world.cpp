#include <sanguis/server/collision/remove_result.hpp>
#include <sanguis/server/entities/combine_remove_from_world.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <fcppt/algorithm/join_move.hpp>


sanguis::server::entities::remove_from_world_result
sanguis::server::entities::combine_remove_from_world(
	sanguis::server::entities::remove_from_world_result &&_left,
	sanguis::server::entities::remove_from_world_result &&_right
)
{
	return
		sanguis::server::entities::remove_from_world_result(
			sanguis::server::collision::remove_result(
				fcppt::algorithm::join_move(
					_left.release_collision_result().release_body_exit(),
					_right.release_collision_result().release_body_exit()
				)
			)
		);
}
