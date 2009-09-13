#include "burn.hpp"
#include "../buffs/burn.hpp"
#include "../entities/entity.hpp"

sanguis::server::auras::burn::burn(
	sge::collision::world_ptr const collision_world_,
	space_unit const radius,
	team::type const team,
	space_unit const damage_per_pulse,
	time_type const pulse_diff,
	damage::array const &damage_values)
:
	aura(
		collision_world_,
		radius,
		team,
		influence::debuff
	),
	pulse_diff(pulse_diff),
	damage_per_pulse(damage_per_pulse),
	damage_values(damage_values)
{}

void sanguis::server::auras::burn::do_effect(
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
