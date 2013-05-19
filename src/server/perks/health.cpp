#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/health.hpp>
#include <sanguis/server/perks/level_diff.hpp>


sanguis::server::perks::health::health()
:
	sanguis::server::perks::perk(
		sanguis::perk_type::health
	)
{
}

sanguis::server::perks::health::~health()
{
}

void
sanguis::server::perks::health::change(
	sanguis::server::entities::base &_entity,
	sanguis::server::perks::level_diff const _diff
)
{
	sanguis::server::perks::change_simple<
		sanguis::server::entities::with_health
	>(
		&sanguis::server::entities::property::constant_change,
		_entity,
		&sanguis::server::entities::with_health::health,
		20.f,
		_diff
	);
}
