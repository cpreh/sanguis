#include "aoe_damage.hpp"
#include "../../auras/burn.hpp"
#include "../../environment/object.hpp"
#include <fcppt/chrono/duration_arithmetic.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
	team::type const _team,
	server::radius const _radius,
	damage::unit const _damage_per_pulse,
	unsigned const _max_pulses,
	sanguis::time_delta const &_pulse_diff,
	damage::array const &_damage_values
)
:
	aoe_projectile(
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
				sanguis::time_delta::rep
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
