#include <sanguis/server/auras/collision_groups.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assign/make_container.hpp>

sanguis::server::collision::group_vector const
sanguis::server::auras::collision_groups(
	team::type const _team,
	influence::type const _influence
)
{
	if (
		(
			_team == team::players
			&& _influence == influence::buff
		)
		||
		(
			_team == team::monsters
			&& _influence == influence::debuff
		)

	)
		return
			fcppt::assign::make_container<
				collision::group_vector
			>(
				collision::group::projectile_enemy
			);

	if (
		(
			_team == team::players
			&& _influence == influence::debuff
		)
		||
		(
			_team == team::monsters
			&& _influence == influence::buff
		)

	)
		return
			fcppt::assign::make_container<
				collision::group_vector
			>(
				collision::group::projectile_player
			);

	FCPPT_ASSERT_UNREACHABLE
}
