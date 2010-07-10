#include "health.hpp"
#include "change_simple.hpp"
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
	perks::change_simple<
		entities::with_health
	>(
		&entities::property::constant_change,
		entity_,
		&entities::with_health::health,
		20.f,
		diff_
	);
}

sanguis::server::perks::level_type
sanguis::server::perks::health::max_level() const
{
	return 10;
}
