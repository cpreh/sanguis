#include "ias.hpp"
#include "diff_factor.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/linear_change.hpp"
#include "../entities/with_weapon.hpp"

sanguis::server::perks::ias::ias()
:
	perk(
		perk_type::ias
	)
{}

void
sanguis::server::perks::ias::change(
	entities::base &entity_,
	level_diff const diff_
)
{
	entities::property::linear_change(
		dynamic_cast<
			entities::with_weapon &
		>(
			entity_
		)
		.attack_speed(),
		diff_factor(
			factor,
			level(),
			diff_
		)
	);
}

bool
sanguis::server::perks::ias::can_raise_level() const
{
	return level() < 8;
}

sanguis::server::entities::property::value const
sanguis::server::perks::ias::factor(
	level_type const level_
)
{
	return
		entities::property::value(
			level_,
			5
		);
}
