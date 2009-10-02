#include "burn.hpp"
#include "../buffs/burn.hpp"
#include "../entities/with_buffs.hpp"
#include <sge/make_auto_ptr.hpp>

sanguis::server::auras::burn::burn(
	space_unit const radius,
	team::type const team,
	damage::unit const damage_per_pulse,
	time_type const pulse_diff,
	damage::array const &damage_values
)
:
	aura(
		radius,
		team,
		influence::debuff
	),
	pulse_diff(pulse_diff),
	damage_per_pulse(damage_per_pulse),
	damage_values(damage_values),
	provider_()
{}

void
sanguis::server::auras::burn::enter(
	entities::base &entity_
)
{
	buffs::auto_ptr new_buff(
		sge::make_auto_ptr<
			buffs::burn
		>(
			damage_per_pulse,
			pulse_diff,
			1,
			damage_values
		)
	);

	provider_.add(
		dynamic_cast<
			entities::with_buffs &
		>(
			entity_
		),
		new_buff
	);
}

void
sanguis::server::auras::burn::leave(
	entities::base &entity_
)
{
	provider_.remove(
		dynamic_cast<
			entities::with_buffs &
		>(
			entity_
		)
	);
}
