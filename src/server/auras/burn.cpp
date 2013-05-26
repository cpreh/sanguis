#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/burn.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::auras::burn::burn(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::radius const _radius,
	sanguis::server::team const _team,
	sanguis::server::auras::burn::damage_per_pulse const _damage_per_pulse,
	sanguis::server::auras::burn::pulse_time const &_pulse_time,
	sanguis::server::damage::array const &_damage_values
)
:
	sanguis::server::auras::aura(
		_radius,
		_team,
		sanguis::server::auras::influence::debuff
	),
	diff_clock_(
		_diff_clock
	),
	pulse_time_(
		_pulse_time
	),
	damage_per_pulse_(
		_damage_per_pulse
	),
	damage_values_(
		_damage_values
	),
	provider_()
{
}

sanguis::server::auras::burn::~burn()
{
}

void
sanguis::server::auras::burn::enter(
	sanguis::server::entities::with_body &_entity
)
{
	provider_.add(
		dynamic_cast<
			sanguis::server::entities::with_buffs &
		>(
			_entity
		),
		sanguis::server::buffs::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::server::buffs::burn
			>(
				diff_clock_,
				sanguis::server::buffs::burn::damage_per_pulse(
					damage_per_pulse_.get()
				),
				sanguis::server::buffs::burn::pulse_time(
					pulse_time_.get()
				),
				sanguis::server::buffs::burn::max_pulses(
					1u
				),
				damage_values_
			)
		)
	);
}

void
sanguis::server::auras::burn::leave(
	sanguis::server::entities::with_body &_entity
)
{
	provider_.remove(
		dynamic_cast<
			sanguis::server::entities::with_buffs &
		>(
			_entity
		)
	);
}
