#include "burn.hpp"
#include "../entities/with_health.hpp"
#include <sge/timer/reset_when_expired.hpp>

sanguis::server::buffs::burn::burn(
	sanguis::diff_clock const &_diff_clock,
	damage::unit const _damage,
	sanguis::duration const &_pulse_time,
	unsigned const _max_pulses,
	damage::array const &_damage_values
)
:
	buff(),
	damage_(_damage),
	pulse_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_pulse_time
		)
		.expired(
			true
		)
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
	entities::base &_ref
)
{
	if(
		!sge::timer::reset_when_expired(
			pulse_timer_
		)
	)
		return;
	
	if(
		pulses_++ == max_pulses_
	)
	{
		this->expire();

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
