#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/server/collision/remove_result.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::remove_from_world_result::remove_from_world_result()
:
	collision_result_(
		sanguis::server::collision::remove_result(
			sanguis::collision::world::body_exit_container()
		)
	)
{
}

sanguis::server::entities::remove_from_world_result::remove_from_world_result(
	sanguis::server::collision::remove_result &&_collision_result
)
:
	collision_result_(
		std::move(
			_collision_result
		)
	)
{
}

sanguis::server::collision::remove_result const &
sanguis::server::entities::remove_from_world_result::collision_result() const
{
	return
		collision_result_;
}

sanguis::server::collision::remove_result &&
sanguis::server::entities::remove_from_world_result::release_collision_result()
{
	return
		std::move(
			collision_result_
		);
}

