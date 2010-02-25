#include "regeneration.hpp"
#include "diff_factor.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/constant_change.hpp"
#include "../entities/with_health.hpp"

sanguis::server::perks::regeneration::regeneration()
:
	perk(
		perk_type::regeneration
	)
{}

void
sanguis::server::perks::regeneration::change(
	entities::base &entity_,
	level_diff const diff_
)
{
	entities::property::constant_change(
		dynamic_cast<
			entities::with_health &
		>(
			entity_
		)
		.regeneration(),
		diff_factor(
			factor,
			level(),
			diff_
		)
	);
}

bool
sanguis::server::perks::regeneration::can_raise_level() const
{
	return level() < 3;
}

sanguis::server::entities::property::value const
sanguis::server::perks::regeneration::factor(
	level_type const level_
)
{
	return
		entities::property::value(
			level_ * 3,
			4
		);
}
