#include "regeneration.hpp"
#include "change_simple.hpp"
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
	perks::change_simple<
		entities::with_health
	>(
		&entities::property::constant_change,
		entity_,
		&entities::with_health::regeneration,
		0.75f,
		diff_
	);
}

sanguis::server::perks::level_type
sanguis::server::perks::regeneration::max_level() const
{
	return 3;
}
