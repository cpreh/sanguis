#include "health.hpp"
#include "diff_factor.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/constant_change.hpp"
#include "../entities/with_health.hpp"

sanguis::server::perks::health::health()
:
	perk(
		perk_type::health
	)
{}

void
sanguis::server::perks::health::change(
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
		.health(),
		diff_factor(
			factor,
			level(),
			diff_
		)
	);
}

bool
sanguis::server::perks::health::can_raise_level() const
{
	return level() < 10;
}

sanguis::server::entities::property::value const
sanguis::server::perks::health::factor(
	level_type const level_
)
{
	return
		sanguis::server::entities::property::value(
			level_ * 20,
			1
		);
}
