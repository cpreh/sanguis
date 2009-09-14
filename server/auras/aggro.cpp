#include "aggro.hpp"

sanguis::server::auras::aggro::aggro(
	sge::collision::world_ptr const collision_world_,
	space_unit const radius_,
	team::type const team_,
	update_target_function const &update_target_
)
:
	aura(
		collision_world_,
		radius_,
		team_,
		influence::debuff
	),
	update_target_(
		update_target_
	)
{}

void
sanguis::server::auras::aggro::do_effect(
	entities::entity &target
)
{
	update_target_(
		target
	);
}
