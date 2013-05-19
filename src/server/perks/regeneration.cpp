#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/regeneration.hpp>


sanguis::server::perks::regeneration::regeneration()
:
	perk(
		sanguis::perk_type::regeneration
	)
{
}

sanguis::server::perks::regeneration::~regeneration()
{
}

void
sanguis::server::perks::regeneration::change(
	sanguis::server::entities::base &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::change_simple<
		sanguis::server::entities::with_health
	>(
		&sanguis::server::entities::property::constant_change,
		_entity,
		&sanguis::server::entities::with_health::regeneration,
		0.75f,
		_diff
	);
}
