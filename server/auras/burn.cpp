#include "burn.hpp"
#include "../buffs/burn.hpp"
#include "../entities/entity.hpp"

sanguis::server::auras::burn::burn(
	space_unit const radius,
	team::type const team,
	space_unit const damage_per_pulse,
	time_type const pulse_diff,
	damage::array const &damage_values)
:
	aura(
		radius,
		team,
		influence::debuff
	),
	pulse_diff(pulse_diff),
	damage_per_pulse(damage_per_pulse),
	damage_values(damage_values)
{}

void
sanguis::server::auras::burn::enter(
	entities::entity &e
)
{
	e.add_buff(
		buffs::auto_ptr(
			new buffs::burn(
				owner(),
				damage_per_pulse,
				pulse_diff,
				1,
				damage_values
			)
		)
	);
}

void
sanguis::server::auras::burn::leave(
	entities::entity &
)
{
	// FIXME: remove the buff!
}
