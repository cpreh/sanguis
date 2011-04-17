#include "irs.hpp"
#include "change_simple.hpp"
#include "../entities/property/linear_change.hpp"
#include "../entities/with_weapon.hpp"

sanguis::server::perks::irs::irs()
:
	perk(
		perk_type::irs
	)
{
}

sanguis::server::perks::irs::~irs()
{
}

void
sanguis::server::perks::irs::change(
	entities::base &_entity,
	level_diff const _diff
)
{
	perks::change_simple<
		entities::with_weapon
	>(
		&entities::property::linear_change,
		_entity,
		&entities::with_weapon::reload_speed,
		0.5f,
		_diff
	);
}
