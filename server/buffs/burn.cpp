#include "burn.hpp"
#include "../entities/entity.hpp"
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>

sanguis::server::buffs::burn::burn(
	entity_id const source_,
	space_unit const damage,
	time_type const pulse_time,
	unsigned const max_pulses,
	damage::array const &damage_values)
:
	buff(
		source_
	),
	damage(damage),
	clock_(),
	pulse_timer(
		sge::time::second_f(
			pulse_time
		),
		sge::time::activation_state::active,
		clock_.callback(),
		sge::time::expiration_state::expired
	),
	pulses(0),
	max_pulses(max_pulses),
	damage_values(damage_values)
{}

void
sanguis::server::buffs::burn::update(
	entities::entity &ref,
	time_type const diff)
{
	clock_.update(diff);

	if(!pulse_timer.update_b())
		return;
	
	if(pulses++ == max_pulses)
	{
		expire();
		return;
	}

	ref.damage(
		damage,
		damage_values
	);
}
