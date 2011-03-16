#include "health.hpp"
#include "change_simple.hpp"
#include "../entities/property/constant_change.hpp"
#include "../entities/with_health.hpp"

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

sanguis::server::perks::level_type
sanguis::server::perks::health::max_level() const
{
	return 10;
}
