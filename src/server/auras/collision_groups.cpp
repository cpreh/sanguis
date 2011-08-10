#include "collision_groups.hpp"
#include "../../exception.hpp"
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>

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

	throw sanguis::exception(
		FCPPT_TEXT("Don't know a collision group for an aura.")
	);
}
