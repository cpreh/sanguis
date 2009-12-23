#include "collision_groups.hpp"
#include "../../exception.hpp"
#include <sge/assign/make_container.hpp>
#include <fcppt/text.hpp>

sanguis::server::collision::group_vector const
sanguis::server::auras::collision_groups(
	team::type const team_,
	influence::type const influence_
)
{
	if (
		(
			team_ == team::players
			&& influence_ == influence::buff
		)
		||
		(
			team_ == team::monsters
			&& influence_ == influence::debuff
		)

	)
		return
			sge::assign::make_container<
				collision::group_vector
			>(
				collision::group::projectile_enemy
			);
	
	if (
		(
			team_ == team::players
			&& influence_ == influence::debuff
		)
		||
		(
			team_ == team::monsters
			&& influence_ == influence::buff
		)

	)
		return
			sge::assign::make_container<
				collision::group_vector
			>(
				collision::group::projectile_player
			);

	throw exception(
		FCPPT_TEXT("Don't know a collision group for an aura.")
	);
}
