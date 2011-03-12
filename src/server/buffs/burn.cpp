#include "burn.hpp"
#include "../entities/with_health.hpp"
#include <sge/time/second_f.hpp>

sanguis::server::buffs::burn::burn(
	damage::unit const _damage,
	time_type const _pulse_time,
	unsigned const _max_pulses,
	damage::array const &_damage_values
)
:
	buff(),
	damage_(_damage),
	clock_(),
	pulse_timer_(
		sge::time::second_f(
			_pulse_time
		),
		sge::time::activation_state::active,
		clock_.callback(),
		sge::time::expiration_state::expired
	),
	pulses_(0),
	max_pulses_(_max_pulses),
	damage_values_(_damage_values)
{
}

sanguis::server::buffs::burn::~burn()
{
}

void
sanguis::server::buffs::burn::update(
	entities::base &_ref,
	time_type const _diff
)
{
	clock_.update(
		_diff
	);

	if(
		!pulse_timer_.update_b()
	)
		return;
	
	if(
		pulses_++ == max_pulses_
	)
	{
		expire();
		return;
	}

	dynamic_cast<
		entities::with_health &
	>(
		_ref
	).damage(
		damage_,
		damage_values_
	);
}
