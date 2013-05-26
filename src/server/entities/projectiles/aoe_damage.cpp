#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/burn.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/projectiles/damage_per_pulse.hpp>
#include <sanguis/server/entities/projectiles/indeterminate.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/pulse_time.hpp>
#include <sanguis/server/entities/projectiles/pulses.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/math/dim/arithmetic.hpp>


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
	sanguis::server::entities::projectiles::aoe_projectile(
		_diff_clock,
		sanguis::aoe_projectile_type::aoe_damage,
		_team,
		sanguis::server::entities::movement_speed(
			0.f
		),
		sanguis::server::dim(
			_radius.get(),
			_radius.get()
		)
		*
		static_cast<
			sanguis::server::dim::value_type
		>(
			2
		),
		sanguis::server::entities::projectiles::life_time(
			_pulse_time.get()
			*
			static_cast<
				sanguis::duration::rep
			>(
				_pulses.get()
			)
		),
		sanguis::server::entities::projectiles::indeterminate::yes,
		_radius,
		sanguis::server::direction(
			0.f
		)
	),
	sanguis::server::entities::with_auras()
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

void
sanguis::server::entities::projectiles::aoe_damage::do_damage(
	sanguis::server::entities::with_health &
)
{
}
