#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sge/timer/reset_when_expired.hpp>


sanguis::server::buffs::burn::burn(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::buffs::burn::damage_per_pulse const _damage_per_pulse,
	sanguis::server::buffs::burn::pulse_time const &_pulse_time,
	sanguis::server::buffs::burn::max_pulses const _max_pulses,
	sanguis::server::damage::array const &_damage_values
)
:
	sanguis::server::buffs::buff(),
	damage_per_pulse_(
		_damage_per_pulse
	),
	pulse_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_pulse_time.get()
		)
		.expired(
			true
		)
	),
	pulses_(
		0u
	),
	max_pulses_(
		_max_pulses
	),
	damage_values_(
		_damage_values
	)
{
}

sanguis::server::buffs::burn::~burn()
{
}

void
sanguis::server::buffs::burn::update(
	sanguis::server::entities::base &_ref
)
{
	if(
		!sge::timer::reset_when_expired(
			pulse_timer_
		)
	)
		return;

	if(
		pulses_++ == max_pulses_.get()
	)
	{
		this->expire();

		return;
	}

	dynamic_cast<
		sanguis::server::entities::with_health &
	>(
		_ref
	).damage(
		damage_per_pulse_.get(),
		damage_values_
	);
}
