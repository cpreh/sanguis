#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/wrapper.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <sanguis/server/entities/projectiles/damage_per_pulse.hpp>
#include <sanguis/server/entities/projectiles/melee.hpp>
#include <sanguis/server/entities/projectiles/pulses.hpp>
#include <sanguis/server/entities/projectiles/pulse_time.hpp>


sanguis::server::entities::projectiles::melee::melee(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::team const _team,
	sanguis::server::damage::unit const _damage
)
:
	// TODO: This is a stupid hack
	sanguis::server::entities::projectiles::aoe_damage(
		_diff_clock,
		_team,
		sanguis::server::radius(
			1.f
		),
		sanguis::server::entities::projectiles::damage_per_pulse(
			_damage
		),
		sanguis::server::entities::projectiles::pulses(
			1u
		),
		sanguis::server::entities::projectiles::pulse_time(
			sanguis::duration_second(
				0
			)
		),
		sanguis::server::damage::list(
			sanguis::server::damage::normal =
				sanguis::server::damage::full
		)
	)
{
}

sanguis::server::entities::projectiles::melee::~melee()
{
}
