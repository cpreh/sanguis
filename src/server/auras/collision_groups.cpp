#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/collision_groups.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assign/make_container.hpp>


sanguis::server::collision::group_vector
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
			fcppt::assign::make_container<
				sanguis::server::collision::group_vector
			>(
				sanguis::server::collision::group::projectile_enemy
			);

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
			fcppt::assign::make_container<
				sanguis::server::collision::group_vector
			>(
				sanguis::server::collision::group::projectile_player
			);

	FCPPT_ASSERT_UNREACHABLE;
}
