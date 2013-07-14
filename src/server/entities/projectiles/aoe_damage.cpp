#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/burn.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <sanguis/server/entities/projectiles/damage_per_pulse.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/pulse_time.hpp>
#include <sanguis/server/entities/projectiles/pulses.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::team const _team,
	sanguis::server::radius const _radius,
	sanguis::server::entities::projectiles::damage_per_pulse const _damage_per_pulse,
	sanguis::server::entities::projectiles::pulses const _pulses,
	sanguis::server::entities::projectiles::pulse_time const &_pulse_time,
	sanguis::server::damage::array const &_damage_values
)
:
	sanguis::server::entities::with_auras(),
	sanguis::server::entities::center_ghost(),
	life_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_pulse_time.get()
			*
			static_cast<
				sanguis::duration::rep
			>(
				_pulses.get()
			)
		)
	)
{
	this->add_aura(
		fcppt::make_unique_ptr<
			sanguis::server::auras::burn
		>(
			_diff_clock,
			_radius,
			_team,
			sanguis::server::auras::burn::damage_per_pulse(
				_damage_per_pulse.get()
			),
			sanguis::server::auras::burn::pulse_time(
				_pulse_time.get()
			),
			_damage_values
		)
	);
}

sanguis::server::entities::projectiles::aoe_damage::~aoe_damage()
{
}

bool
sanguis::server::entities::projectiles::aoe_damage::dead() const
{
	return
		life_timer_.expired();
}
