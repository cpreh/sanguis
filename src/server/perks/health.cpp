#include <sanguis/server/perks/health.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/entities/with_health.hpp>

sanguis::server::perks::health::health()
:
	perk(
		perk_type::health
	)
{
}

sanguis::server::perks::health::~health()
{
}

void
sanguis::server::perks::health::change(
	entities::base &_entity,
	level_diff const _diff
)
{
	perks::change_simple<
		entities::with_health
	>(
		&entities::property::constant_change,
		_entity,
		&entities::with_health::health,
		20.f,
		_diff
	);
}
