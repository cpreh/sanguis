#include "aggro.hpp"

sanguis::server::auras::aggro::aggro(
	space_unit const radius_,
	team::type const team_,
	update_target_function const &update_target_
)
:
	aura(
		radius_,
		team_,
		influence::debuff
	),
	update_target_(
		update_target_
	)
{}

void
sanguis::server::auras::aggro::enter(
	entities::entity &target
)
{
	update_target_(
		target
	);
}

void
sanguis::server::auras::aggro::leave(
	entities::entity &target
)
{
	// FIXME!
}
