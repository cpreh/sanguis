#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <sanguis/server/auras/burn.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/chrono/duration_arithmetic.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
	sanguis::diff_clock const &_diff_clock,
	team::type const _team,
	server::radius const _radius,
	damage::unit const _damage_per_pulse,
	unsigned const _max_pulses,
	sanguis::duration const &_pulse_diff,
	damage::array const &_damage_values
)
:
	aoe_projectile(
		_diff_clock,
		aoe_projectile_type::aoe_damage,
		_team,
		entities::movement_speed(0),
		server::dim(
			_radius.get(),
			_radius.get()
		)
		*
		static_cast<
			server::dim::value_type
		>(
			2
		),
		projectiles::life_time(
			_pulse_diff
			*
			static_cast<
				sanguis::duration::rep
			>(
				_max_pulses
			)
		),
		indeterminate::yes,
		_radius,
		server::direction(
			0
		)
	)
{
	this->add_aura(
		auras::unique_ptr(
			fcppt::make_unique_ptr<
				auras::burn
			>(
				fcppt::cref(
					_diff_clock
				),
				_radius,
				_team,
				_damage_per_pulse,
				_pulse_diff,
				_damage_values
			)
		)
	);
}

sanguis::server::entities::projectiles::aoe_damage::~aoe_damage()
{
}

void
sanguis::server::entities::projectiles::aoe_damage::do_damage(
	with_health &
)
{
}
