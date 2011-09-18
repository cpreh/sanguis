#include <sanguis/server/perks/irs.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/entities/with_weapon.hpp>

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
