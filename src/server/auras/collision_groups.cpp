#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/group_vector.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/collision_groups.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::collision::world::group_vector
sanguis::server::auras::collision_groups(
	sanguis::server::team const _team,
	sanguis::server::auras::influence const _influence
)
{
	if(
		(
			_team == sanguis::server::team::players
			&& _influence == sanguis::server::auras::influence::buff
		)
		||
		(
			_team == sanguis::server::team::monsters
			&& _influence == sanguis::server::auras::influence::debuff
		)

	)
		return
			sanguis::collision::world::group_vector{
				sanguis::collision::world::group::projectile_enemy
			};

	if(
		(
			_team == sanguis::server::team::players
			&& _influence == sanguis::server::auras::influence::debuff
		)
		||
		(
			_team == sanguis::server::team::monsters
			&& _influence == sanguis::server::auras::influence::buff
		)

	)
		return
			sanguis::collision::world::group_vector{
				sanguis::collision::world::group::projectile_player
			};

	FCPPT_ASSERT_UNREACHABLE;
}
