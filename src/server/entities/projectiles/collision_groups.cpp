#include <sanguis/server/team.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/entities/projectiles/collision_groups.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::server::collision::group_vector
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
			sanguis::server::collision::group_vector{
				sanguis::server::collision::group::projectile_player
			};
	case sanguis::server::team::monsters:
		return
			sanguis::server::collision::group_vector{
				sanguis::server::collision::group::projectile_enemy
			};
	case sanguis::server::team::neutral:
		return
			sanguis::server::collision::group_vector(); // TODO: Does this even matter?
	}

	FCPPT_ASSERT_UNREACHABLE;
}
