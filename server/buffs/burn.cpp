#include "burn.hpp"
#include "../entities/with_health.hpp"
#include <sge/time/second_f.hpp>

sanguis::server::buffs::burn::burn(
	damage::unit const damage_,
	time_type const pulse_time,
	unsigned const max_pulses,
	damage::array const &damage_values
)
:
	buff(),
	damage_(damage_),
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
	entities::base &ref,
	time_type const diff
)
{
	clock_.update(diff);

	if(!pulse_timer.update_b())
		return;
	
	if(pulses++ == max_pulses)
	{
		expire();
		return;
	}

	dynamic_cast<
		entities::with_health &
	>(
		ref
	).damage(
		damage_,
		damage_values
	);
}
