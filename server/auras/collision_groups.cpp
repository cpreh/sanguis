#include "collision_groups.hpp"
#include <sge/assign/make_container.hpp>

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

	// TODO:
	return collision::group_vector();
}
