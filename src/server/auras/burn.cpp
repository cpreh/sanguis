#include <sanguis/server/auras/burn.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::auras::burn::burn(
	sanguis::diff_clock const &_diff_clock,
	server::radius const _radius,
	server::team::type const _team,
	damage::unit const _damage_per_pulse,
	sanguis::duration const &_pulse_diff,
	damage::array const &_damage_values
)
:
	aura(
		_radius,
		_team,
		influence::debuff
	),
	diff_clock_(_diff_clock),
	pulse_diff_(_pulse_diff),
	damage_per_pulse_(_damage_per_pulse),
	damage_values_(_damage_values),
	provider_()
{
}

sanguis::server::auras::burn::~burn()
{
}

void
sanguis::server::auras::burn::enter(
	entities::with_body &_entity
)
{
	provider_.add(
		dynamic_cast<
			entities::with_buffs &
		>(
			_entity
		),
		buffs::unique_ptr(
			fcppt::make_unique_ptr<
				buffs::burn
			>(
				fcppt::cref(
					diff_clock_
				),
				damage_per_pulse_,
				pulse_diff_,
				1u,
				damage_values_
			)
		)
	);
}

void
sanguis::server::auras::burn::leave(
	entities::with_body &_entity
)
{
	provider_.remove(
		dynamic_cast<
			entities::with_buffs &
		>(
			_entity
		)
	);
}
