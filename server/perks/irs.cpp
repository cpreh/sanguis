#include "irs.hpp"
#include "change_simple.hpp"
#include "../entities/property/linear_change.hpp"
#include "../entities/with_weapon.hpp"

sanguis::server::perks::irs::irs()
:
	perk(
		perk_type::irs
	)
{}

void
sanguis::server::perks::irs::change(
	entities::base &entity_,
	level_diff const diff_
)
{
	perks::change_simple<
		entities::with_weapon
	>(
		&entities::property::linear_change,
		entity_,
		&entities::with_weapon::reload_speed,
		0.5f,
		diff_
	);
}

sanguis::server::perks::level_type
sanguis::server::perks::irs::max_level() const
{
	return 4;
}
