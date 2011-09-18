#include <sanguis/server/perks/regeneration.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/entities/with_health.hpp>

sanguis::server::perks::regeneration::regeneration()
:
	perk(
		perk_type::regeneration
	)
{
}

sanguis::server::perks::regeneration::~regeneration()
{
}

void
sanguis::server::perks::regeneration::change(
	entities::base &_entity,
	level_diff const _diff
)
{
	perks::change_simple<
		entities::with_health
	>(
		&entities::property::constant_change,
		_entity,
		&entities::with_health::regeneration,
		0.75f,
		_diff
	);
}
