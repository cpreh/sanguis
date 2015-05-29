#include <sanguis/server/entities/combine_remove_from_world.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <fcppt/algorithm/join.hpp>


sanguis::server::entities::remove_from_world_result
sanguis::server::entities::combine_remove_from_world(
	sanguis::server::entities::remove_from_world_result &&_left,
	sanguis::server::entities::remove_from_world_result &&_right
)
{
	return
		sanguis::server::entities::remove_from_world_result(
			fcppt::algorithm::join(
				_left.release_body_exit(),
				_right.release_body_exit()
			)
		);
}
