#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/group_vector.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/projectiles/collision_groups.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::collision::world::group_vector
sanguis::server::entities::projectiles::collision_groups(
	sanguis::server::team const _team
)
{
	switch(
		_team
	)
	{
	case sanguis::server::team::players:
		return
			sanguis::collision::world::group_vector{
				sanguis::collision::world::group::projectile_player
			};
	case sanguis::server::team::monsters:
		return
			sanguis::collision::world::group_vector{
				sanguis::collision::world::group::projectile_enemy
			};
	case sanguis::server::team::neutral:
		return
			sanguis::collision::world::group_vector(); // TODO: Does this even matter?
	}

	FCPPT_ASSERT_UNREACHABLE;
}
